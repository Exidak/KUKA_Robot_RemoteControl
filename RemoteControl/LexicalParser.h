#pragma once

#include <string>
#include <vector>

typedef unsigned int uint;

class LexicalParser
{
public:
	typedef struct DictElem
	{
		char *Lexem;
		int Id;
		uint LexemSize;
	} DictElem;

	typedef std::vector<DictElem> LexDictionary;

	enum EParserFlag : int
	{
		IgnoreTab = 1,
		IgnoreEndLine = 2
	};

	enum ETermType : int
	{
		UnknownTerm = 0,
		ReservedWord = 1,
		StringTerm = 2,
		IntegerTerm = 3,
		DoubleTerm = 4,
		EndLineTerm = 5,
		TabTerm = 6
	};

	enum ENumberState : int
	{
		PrefixState = 0,
		IntState = 1,
		EndState = 2,
		DotState = 3,
		ExpState = 4,
		ExpDigitState = 5,
		ExpPrefState = 6,
		ErrorState = 7
	};

	class CError {
	public:
		int m_Err_code;
		uint m_Line;
		uint m_position;

		CError(int Err_code, uint Line, uint position) : m_Err_code(Err_code), m_Line(Line), m_position(position) {}
	};

	class CBaseTerm
	{
	public:
		ETermType m_TermType;
		uint m_Position;
		uint m_Line;

		CBaseTerm(
			ETermType TermType = UnknownTerm,
			uint Position = 0,
			uint Line = 0)
			: m_TermType(TermType), m_Position(Position), m_Line(Line) {}
		CBaseTerm(const CBaseTerm &arg)
			: m_TermType(arg.m_TermType), m_Position(arg.m_Position), m_Line(arg.m_Line) {}

		virtual ~CBaseTerm() {}
	};

	class CWordTerm : public  CBaseTerm
	{
	public:
		int m_Id;

		CWordTerm(
			ETermType TermType = UnknownTerm,
			uint Position = 0,
			uint Line = 0,
			int id = 0)
			: CBaseTerm(TermType, Position, Line), m_Id(id) {}
		CWordTerm(const CWordTerm &arg)
			: CBaseTerm(arg.m_TermType, arg.m_Position, arg.m_Line), m_Id(arg.m_Id) {}

		virtual ~CWordTerm() {}
	};

	class CStringTerm : public CBaseTerm
	{
	public:
		std::string m_Value;

		CStringTerm(
			ETermType TermType = UnknownTerm,
			uint Position = 0,
			uint Line = 0,
			std::string Value = 0)
			: CBaseTerm(TermType, Position, Line), m_Value(Value) {}
		CStringTerm(const CStringTerm &arg)
			: CBaseTerm(arg.m_TermType, arg.m_Position, arg.m_Line), m_Value(arg.m_Value) {}

		virtual ~CStringTerm() {}
	};

	class CIntegerTerm : public CBaseTerm
	{
	public:
		int m_Value;

		CIntegerTerm(
			ETermType TermType = UnknownTerm,
			uint Position = 0,
			uint Line = 0,
			int Value = 0)
			: CBaseTerm(TermType, Position, Line), m_Value(Value) {}
		CIntegerTerm(const CIntegerTerm &arg)
			: CBaseTerm(arg.m_TermType, arg.m_Position, arg.m_Line), m_Value(arg.m_Value) {}

		virtual ~CIntegerTerm() {}
	};

	class CDoubleTerm : public CBaseTerm
	{
	public:
		double m_Value;

		CDoubleTerm(
			ETermType TermType = UnknownTerm,
			uint Position = 0,
			uint Line = 0,
			double Value = 0)
			: CBaseTerm(TermType, Position, Line), m_Value(Value) {}
		CDoubleTerm(const CDoubleTerm &arg)
			: CBaseTerm(arg.m_TermType, arg.m_Position, arg.m_Line), m_Value(arg.m_Value) {}

		virtual ~CDoubleTerm() {}
	};

	typedef std::shared_ptr<CBaseTerm> CBaseTermPtr;
	typedef std::vector<CBaseTermPtr> BaseTermList;
	typedef std::vector<CError*> CErrorList;

	// Text UTF-8
	// C-standart strings
	static BaseTermList parseTextToLexem(LexDictionary &Dictionary, const char* Text, CErrorList &Err_List, int Flags);

	// get values 
	static int getReservedWordId(CBaseTermPtr BaseTerm);
	static std::string getStringValue(CBaseTermPtr BaseTerm);
	static int getIntegerValue(CBaseTermPtr BaseTerm);
	static double getDoubleValue(CBaseTermPtr BaseTerm);
};

