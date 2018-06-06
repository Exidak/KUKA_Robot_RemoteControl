#include "stdafx.h"
#include "error_codes.h"
#include "LexicalParser.h"


LexicalParser::BaseTermList LexicalParser::parseTextToLexem(LexDictionary &Dictionary, const char* Text, CErrorList &Err_List, int Flags)
{
	std::string TextCpy = Text;
	if (!TextCpy.size())
		return LexicalParser::BaseTermList();

	//TextCpy.push_back('\0');
	char *Buf = &*TextCpy.begin();

	BaseTermList TermsList;
	uint pos_line = 0;
	uint line = 1;

	while (*Buf)
	{
		if (pos_line == 0 && *Buf == '#') // comment
		{
			while (*Buf && *Buf != '\n')
				Buf++;
		}
		else if (*Buf == ' ') // skip spaces
		{
			pos_line++;
		}
		else if (*Buf != '\r') // skip \r
		{
			if (*Buf == '\t') // write term (if no flag ignore) to the term list
			{
				if (!(Flags & IgnoreTab))
				{
					TermsList.push_back(CBaseTermPtr(new CBaseTerm(TabTerm, pos_line, line)));
				}
				pos_line++;
			}
			else if (*Buf == '\n') // write term (if no flag ignore) to the term list
			{
				if (!(Flags & IgnoreEndLine))
				{
					TermsList.push_back(CBaseTermPtr(new CBaseTerm(EndLineTerm, pos_line, line)));
				}
				line++;
				pos_line = 0;
			}
			else if (*Buf == '"') // String term
			{
				Buf++;
				char *old = Buf;
				while (*Buf != '\0')
				{
					if (*Buf == '"' && Buf[-1] != '\\' && Buf[+1] != '"')
					{
						break;
					}
					Buf++;
				}
				if (*Buf == 0)
					Err_List.push_back(new CError(-1, line, pos_line));
				else
				{
					*Buf = 0;
					Buf++;
					// 						std::string Value;
					// 						Value.resize(strlen(old)+1);
					// 						sprintf(&*Value.begin(), old);
					TermsList.push_back(CBaseTermPtr(static_cast<CBaseTerm*>(new CStringTerm(StringTerm, pos_line, line, old/*Value*/))));
					pos_line += (uint)strlen(old) + 1/*Value.size()*/;
					continue;
				}
			}
			else if (((*Buf == '-' || *Buf == '+') && (Buf[1] >= 48 && Buf[1] <= 57)) || (*Buf >= 48 && *Buf <= 57)) // Digit
			{
				ENumberState State;
				bool IsInteger = true;
				char *old = Buf;

				if (*Buf == '-' || *Buf == '+')
					State = PrefixState;
				else if (*Buf >= 48 && *Buf <= 57)
					State = IntState;

				while (State != ErrorState && State != EndState)
				{
					switch (State)
					{
					case PrefixState:
						Buf++;
						if (*Buf >= 48 && *Buf <= 57)
							State = IntState;
						else
							State = ErrorState;
						break;
					case IntState:
						Buf++;
						if (*Buf >= 48 && *Buf <= 57)
							State = IntState;
						else if (*Buf == 'E' || *Buf == 'e')
							State = ExpState;
						else if (*Buf == '.')
							State = DotState;
						else
							State = EndState;
						break;
					case DotState:
						IsInteger = false;
						Buf++;
						if (*Buf >= 48 && *Buf <= 57)
							State = DotState;
						else if (*Buf == 'E' || *Buf == 'e')
							State = ExpState;
						else
							State = EndState;
						break;
					case ExpState:
						IsInteger = false;
						Buf++;
						if (*Buf >= 48 && *Buf <= 57)
							State = ExpDigitState;
						else if (*Buf == '-' || *Buf == '+')
							State = ExpPrefState;
						else
							State = ErrorState;
						break;
					case ExpDigitState:
						Buf++;
						if (*Buf >= 48 && *Buf <= 57)
							State = ExpDigitState;
						else
							State = EndState;
						break;
					case ExpPrefState:
						Buf++;
						if (*Buf >= 48 && *Buf <= 57)
							State = ExpDigitState;
						else
							State = ErrorState;
						break;
					case EndState:
					case ErrorState:
						break;
					}
				}
				if (State == EndState)
				{
					// 						char *word = 0;
					// 						size_t len = (size_t)(Buf - old);
					// 						word = (char *)malloc(len + 1);
					// 						if (word == 0)
					// 							throw(DFW_ERR_MEMORY);
					// 						memcpy(word, Text, len);
					// 						word[len] = 0;

					if (IsInteger)
					{
						long int Value = strtol(old, &Buf, 10);
						if (Value == LONG_MAX || Value == LONG_MIN)
							Err_List.push_back(new CError(-1, line, pos_line));
						TermsList.push_back(CBaseTermPtr(static_cast<CBaseTerm*>(new CIntegerTerm(StringTerm, pos_line, line, Value))));
						pos_line += (uint)(Buf - old);
					}
					else
					{
						double Value = strtod(old, &Buf);
						if (Value == HUGE_VAL)
							Err_List.push_back(new CError(-1, line, pos_line));
						TermsList.push_back(CBaseTermPtr(static_cast<CBaseTerm*>(new CDoubleTerm(StringTerm, pos_line, line, Value))));
						pos_line += (uint)(Buf - old);
					}

				}
				else if (State == ErrorState)
				{
					Err_List.push_back(new CError(-1, line, pos_line));
				}
			}
			else // Reserved word
			{
				bool lexemFound = false;
				for (DictElem dictElem : Dictionary)
				{
					if (!strncmp(Buf, dictElem.Lexem, dictElem.LexemSize))
					{
						TermsList.push_back(CBaseTermPtr(static_cast<CBaseTerm*>(new CWordTerm(ReservedWord, pos_line, line, dictElem.Id))));
						lexemFound = true;
						Buf += dictElem.LexemSize;
						pos_line += dictElem.LexemSize;
						break;
					}
				}
				if (!lexemFound)
				{
					while (*Buf != ' ' && *Buf != '\n' && *Buf != '"')
					{
						Buf++;
						pos_line++;
					}
				}
			}
		}
		Buf++;
	}
	return TermsList;
}

int LexicalParser::getReservedWordId(CBaseTermPtr BaseTerm) throw(...)
{
	if (BaseTerm->m_TermType != ReservedWord)
		throw new CError(RC_ERR_INVALID_TYPE, BaseTerm->m_Line, BaseTerm->m_Position);
	CWordTerm *term_res_word = static_cast<CWordTerm*>(BaseTerm.get());
	return term_res_word->m_Id;
	delete term_res_word;
}
std::string LexicalParser::getStringValue(CBaseTermPtr BaseTerm) throw(...)
{
	if (BaseTerm->m_TermType != StringTerm)
		throw new CError(RC_ERR_INVALID_TYPE, BaseTerm->m_Line, BaseTerm->m_Position);
	CStringTerm *term_string = static_cast<CStringTerm*>(BaseTerm.get());
	return term_string->m_Value;
	delete term_string;
}
int LexicalParser::getIntegerValue(CBaseTermPtr BaseTerm) throw(...)
{
	if (BaseTerm->m_TermType == StringTerm)
		throw new CError(RC_ERR_INVALID_TYPE, BaseTerm->m_Line, BaseTerm->m_Position);
	CIntegerTerm *term_int = static_cast<CIntegerTerm*>(BaseTerm.get());
	return term_int->m_Value;
	delete term_int;
}
double LexicalParser::getDoubleValue(CBaseTermPtr BaseTerm) throw(...)
{
	if (BaseTerm->m_TermType == StringTerm)
		throw new CError(RC_ERR_INVALID_TYPE, BaseTerm->m_Line, BaseTerm->m_Position);
	CDoubleTerm *term_double = static_cast<CDoubleTerm*>(BaseTerm.get());
	return term_double->m_Value;
	delete term_double;
}
