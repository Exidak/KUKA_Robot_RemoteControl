#pragma once

#include <fstream>
#include <streambuf>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "ComInterpreter.h"
#include "error_codes.h"

class ScriptParser
{
public:
	ScriptParser();
	~ScriptParser();

	bool connect();
	std::vector<std::string> getSavedScripts();
	std::string getScriptText(std::string name);

	void runScript(std::string &script, bool isUtf8 = true);
	void runScriptFromFile(std::string path, bool isUtf8 = true);

	struct ScriptError
	{
		ScriptError(int p, EErrCode e) : err(e), pos(p) {}
		EErrCode err;
		int pos;
	};
private:
	enum ELexType
	{
		LexNumber,
		LexReserved,
		LexWord,
	};

	class BaseLexem
	{
	public:
		BaseLexem(ELexType t, int p)
			: type(t), position(p) {}
		ELexType type;
		int position;
	};
	class NumberLexem : public BaseLexem
	{
	public:
		NumberLexem(ELexType t, int p, int s)
			: BaseLexem(t, p), num(s) {}
		int num;
	};
	class ReservedLexem : public BaseLexem
	{
	public:
		ReservedLexem(ELexType t, int p, ECommand s)
			: BaseLexem(t, p), com(s) {}
		ECommand com;
	};
	class WordLexem : public BaseLexem
	{
	public:
		WordLexem(ELexType t, int p, std::string s)
			: BaseLexem(t,p), str(s) {}
		std::string str;
	};

	typedef std::shared_ptr<BaseLexem> BaseLexemPtr;
	typedef std::vector<BaseLexemPtr> vecLexems;
	typedef std::map<std::string, ECommand> MapDict;

	vecLexems parseScript(std::string &script, bool isUtf8 = true);
	void processFunction(vecLexems::iterator &itBeg, vecLexems::iterator &itEnd);
	void processMove(vecLexems::iterator &itBeg, vecLexems::iterator &itEnd);
	void processRotate(vecLexems::iterator &itBeg, vecLexems::iterator &itEnd);
	void processWait(vecLexems::iterator &itBeg, vecLexems::iterator &itEnd);
protected:
	ComInterpreter * m_com;
	MapDict m_Dictionary;
};

