#include "stdafx.h"
#include <filesystem>
#include "str_helper.h"
#include "ScriptParser.h"

namespace fs = std::experimental::filesystem;


ScriptParser::ScriptParser()
{
	m_com = new ComInterpreter();
/*
	m_Dictionary.insert({ "function", RC_CMD_FUNCTION });
	m_Dictionary.insert({ "begin", RC_CMD_BEGIN });
	m_Dictionary.insert({ "end", RC_CMD_END });
	m_Dictionary.insert({ "move", RC_CMD_MOVE });
	m_Dictionary.insert({ "rotate", RC_CMD_ROTATE });
	m_Dictionary.insert({ "stop", RC_CMD_STOP });
	m_Dictionary.insert({ "forward", RC_CMD_FWD });
	m_Dictionary.insert({ "backward", RC_CMD_BCW });
	m_Dictionary.insert({ "right", RC_CMD_RIGHT });
	m_Dictionary.insert({ "left", RC_CMD_LEFT });
	m_Dictionary.insert({ "wait", RC_CMD_WAIT });
	m_Dictionary.insert({ "arm", RC_CMD_ARM_PLATFORM_ROTATE });
*/
	m_Dictionary.insert({ "функция", RC_CMD_FUNCTION });
	m_Dictionary.insert({ "начало", RC_CMD_BEGIN });
	m_Dictionary.insert({ "конец", RC_CMD_END });
	m_Dictionary.insert({ "движение", RC_CMD_MOVE });
	m_Dictionary.insert({ "поворот", RC_CMD_ROTATE });
	m_Dictionary.insert({ "стоп", RC_CMD_STOP });
	m_Dictionary.insert({ "вперед", RC_CMD_FWD });
	m_Dictionary.insert({ "назад", RC_CMD_BCW });
	m_Dictionary.insert({ "вправо", RC_CMD_RIGHT });
	m_Dictionary.insert({ "влево", RC_CMD_LEFT });
	m_Dictionary.insert({ "ждать", RC_CMD_WAIT });
	m_Dictionary.insert({ "рука", RC_CMD_ARM_PLATFORM_ROTATE });

	// read functions
	if (!fs::is_directory("scripts") || !fs::exists("scripts")) { // Check if src folder exists
		fs::create_directory("scripts"); // create src folder
	}
}


ScriptParser::~ScriptParser() {}

bool ScriptParser::connect()
{
	return m_com->connect();
}

std::vector<std::string> ScriptParser::getSavedScripts()
{
	std::vector<std::string> vScripts;
	std::string path = "scripts";
	for (auto & p : fs::directory_iterator(path))
	{
		std::string filename = p.path().string().substr(p.path().string().find('\\') + 1);
		vScripts.push_back(filename);
	}
	return vScripts;
}

std::string ScriptParser::getScriptText(std::string name)
{
	std::string filename = "scripts/" + name;
	if (fs::exists(filename))
	{
		std::ifstream t(filename);
		std::string script;

		t.seekg(0, std::ios::end);
		script.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		script.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		return script;
	}
}

void ScriptParser::runScript(std::string & script, bool isUtf8)
{
	vecLexems vLexs = parseScript(script, isUtf8);

	vecLexems::iterator lexEnd = vLexs.end();
	for (vecLexems::iterator lexem = vLexs.begin(); lexem != lexEnd; ++lexem)
	{
		// every command have to begin with reserved word
		if ((*lexem)->type == LexReserved)
		{
			ReservedLexem *reslex = static_cast<ReservedLexem*>(lexem->get());
			switch (reslex->com)
			{
				case RC_CMD_FUNCTION:
					lexem++;
					processFunction(lexem, lexEnd);
					break;
				case RC_CMD_MOVE:
					lexem++;
					processMove(lexem, lexEnd);
					break;
				case RC_CMD_ROTATE:
					lexem++;
					processRotate(lexem, lexEnd);
					break;
				case RC_CMD_STOP:
					m_com->execCommand(RC_CMD_STOP_MOVEMENT);
					break;
				case RC_CMD_WAIT:
					lexem++;
					processWait(lexem, lexEnd);
					break;
				case RC_CMD_ARM_PLATFORM_ROTATE:
					lexem++;
					m_com->execCommand(RC_CMD_ARM_PLATFORM_ROTATE);
					break;
				default:
					throw ScriptError(reslex->position, RC_ERR_SCRIPT_SYNTAX);
			}
			continue;
		}
		else if ((*lexem)->type == LexWord)// or it can be presaved script
		{
			WordLexem *reslex = static_cast<WordLexem*>(lexem->get());
			std::string name = reslex->str;
			//check if script exist
			std::string filename = "scripts/" + name;
			if (fs::exists(filename))
				runScriptFromFile(filename, false);
			else
				throw ScriptError(reslex->position, RC_ERR_SCRIPT_SYNTAX);
		}
		else
			throw ScriptError((*lexem)->position, RC_ERR_SCRIPT_SYNTAX);
	}
}

void ScriptParser::runScriptFromFile(std::string path, bool isUtf8)
{
	std::ifstream t(path);
	std::string script;

	t.seekg(0, std::ios::end);
	script.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	script.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	runScript(script, isUtf8);
}

ScriptParser::vecLexems ScriptParser::parseScript(std::string & script, bool isUtf8)
{
	vecLexems vLexs;
	int pos = 0;
	// get word by word
	char * tempPtr = strtok(&*script.begin(), " \n");
	while (tempPtr)
	{
		std::string lexem;
		if (isUtf8)
		{
			// convert utf8 to cp1251
			const int ssize = (int)strlen(tempPtr);
			char *cpStr = new char[ssize];
			convert_utf8_to_windows1251(tempPtr, cpStr, ssize);
			lexem = cpStr;
		}
		else
			lexem = tempPtr;
		// find in commands
		MapDict::iterator itDicr = m_Dictionary.find(lexem);
		if (itDicr != m_Dictionary.end())
		{
			vLexs.push_back(BaseLexemPtr(static_cast<BaseLexem*>(new ReservedLexem(LexReserved, pos, itDicr->second))));
		}
		else // check if int number
		{
			try {
				int num = std::stoi(lexem);
				vLexs.push_back(BaseLexemPtr(static_cast<BaseLexem*>(new NumberLexem(LexNumber, pos, num))));
			}
			catch (std::invalid_argument)
			{
				// this is word
				vLexs.push_back(BaseLexemPtr(static_cast<BaseLexem*>(new WordLexem(LexWord, pos, lexem))));
			}

		}
		tempPtr = strtok(NULL, "  \n");
		pos++;
	}

	return vLexs;
}

void ScriptParser::processFunction(vecLexems::iterator & itBeg, vecLexems::iterator & itEnd)
{
	std::string script_text;

	if (itBeg != itEnd && (*itBeg)->type == LexWord) // MUST BE SCRIPT NAME
	{
		WordLexem *reslex = static_cast<WordLexem*>(itBeg->get());
		std::string name = reslex->str;

		//check if script already exist
		std::string filename = "scripts/" + name;
		if (fs::exists(filename))
			ScriptError((*itBeg)->position, RC_ERR_SCRIPT_EXIST);

		itBeg++;
		if (itBeg != itEnd && (*itBeg)->type == LexReserved)
		{
			ReservedLexem *bglex = static_cast<ReservedLexem*>(itBeg->get());
			if (bglex->com != RC_CMD_BEGIN)
				throw ScriptError((*itBeg)->position, RC_ERR_SCRIPT_SYNTAX);
			itBeg++;

			while (itBeg != itEnd)
			{
				if ((*itBeg)->type == LexWord)
				{
					WordLexem *reslex = static_cast<WordLexem*>(itBeg->get());
					script_text += reslex->str;
				}
				else if ((*itBeg)->type == LexNumber)
				{
					NumberLexem *reslex = static_cast<NumberLexem*>(itBeg->get());
					script_text += std::to_string(reslex->num);
				}
				else if ((*itBeg)->type == LexReserved)
				{
					ReservedLexem *reslex = static_cast<ReservedLexem*>(itBeg->get());
					if (reslex->com == RC_CMD_END)
						break;
					else
					{
						std::string keyword;
						for (auto dkey : m_Dictionary)
							if (dkey.second == reslex->com)
							{
								keyword = dkey.first;
								break;
							}
						if (keyword.size())
							script_text += keyword;
						else
							throw ScriptError((*itBeg)->position, RC_ERR_SCRIPT_SYNTAX);
					}
				}
				script_text += " ";
				itBeg++;
			}
		}

		// save script
		std::ofstream t(filename);
		if (t)
			t << script_text;
		t.close();
	}
	else
		throw ScriptError((*itBeg)->position, RC_ERR_SCRIPT_SYNTAX);
}

void ScriptParser::processMove(vecLexems::iterator & itBeg, vecLexems::iterator & itEnd)
{
	if (itBeg != itEnd && (*itBeg)->type == LexReserved) // MUST BE DIRECTION
	{
		ReservedLexem *reslex = static_cast<ReservedLexem*>(itBeg->get());
		ECommand cmd4robot;
		if (reslex->com == RC_CMD_FWD)
			cmd4robot = RC_CMD_MOVE_FORWARD;
		else if (reslex->com == RC_CMD_BCW)
			cmd4robot = RC_CMD_MOVE_BACKWARD;
		else if (reslex->com == RC_CMD_RIGHT)
			cmd4robot = RC_CMD_MOVE_RIGHT;
		else if (reslex->com == RC_CMD_LEFT)
			cmd4robot = RC_CMD_MOVE_LEFT;
		else
			throw ScriptError((*itBeg)->position, RC_ERR_SCRIPT_SYNTAX);

		itBeg++;
		if (itBeg != itEnd && (*itBeg)->type == LexNumber) // MUST BE SPEED
		{
			NumberLexem *reslex = static_cast<NumberLexem*>(itBeg->get());
			int speed = reslex->num;

			//EXEC command
			m_com->execCommand(cmd4robot, speed);
		}
		else
			throw ScriptError((*itBeg)->position, RC_ERR_SCRIPT_SYNTAX);
	}
	else
		throw ScriptError((*itBeg)->position, RC_ERR_SCRIPT_SYNTAX);
}

void ScriptParser::processRotate(vecLexems::iterator & itBeg, vecLexems::iterator & itEnd)
{
	if (itBeg != itEnd && (*itBeg)->type == LexReserved) // MUST BE DIRECTION
	{
		ReservedLexem *reslex = static_cast<ReservedLexem*>(itBeg->get());
		ECommand cmd4robot;
		if (reslex->com == RC_CMD_RIGHT)
			cmd4robot = RC_CMD_ROTATE_RIGHT;
		else if (reslex->com == RC_CMD_LEFT)
			cmd4robot = RC_CMD_ROTATE_LEFT;
		else
			throw RC_ERR_SCRIPT_SYNTAX;

		itBeg++;
		if (itBeg != itEnd && (*itBeg)->type == LexNumber) // MUST BE SPEED
		{
			NumberLexem *reslex = static_cast<NumberLexem*>(itBeg->get());
			int speed = reslex->num;

			//EXEC command
			m_com->execCommand(cmd4robot, speed);
		}
		else
			throw RC_ERR_SCRIPT_SYNTAX;
	}
	else
		throw RC_ERR_SCRIPT_SYNTAX;
}

void ScriptParser::processWait(vecLexems::iterator & itBeg, vecLexems::iterator & itEnd)
{
	if (itBeg != itEnd && (*itBeg)->type == LexNumber) // MUST BE SPEED
	{
		NumberLexem *reslex = static_cast<NumberLexem*>(itBeg->get());
		int msecs = reslex->num;

		//EXEC command
		m_com->execCommand(RC_CMD_WAIT, msecs);
	}
	else
		throw RC_ERR_SCRIPT_SYNTAX;
}
