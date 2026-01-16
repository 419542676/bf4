
// Generated from D:/CLionProjects/BIFANG/BIFANGParser.g4 by ANTLR 4.13.1


#include "BIFANGParserListener.h"
#include "BIFANGParserVisitor.h"

#include "BIFANGParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct BIFANGParserStaticData final {
  BIFANGParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  BIFANGParserStaticData(const BIFANGParserStaticData&) = delete;
  BIFANGParserStaticData(BIFANGParserStaticData&&) = delete;
  BIFANGParserStaticData& operator=(const BIFANGParserStaticData&) = delete;
  BIFANGParserStaticData& operator=(BIFANGParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag bifangparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
BIFANGParserStaticData *bifangparserParserStaticData = nullptr;

void bifangparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (bifangparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(bifangparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<BIFANGParserStaticData>(
    std::vector<std::string>{
      "program", "compUnit", "decl", "constDecl", "bType", "constDef", "constInitVal", 
      "varDecl", "varDef", "initVal", "funcDef", "funcType", "funcFParams", 
      "funcFParam", "block", "blockItem", "stmt", "exp", "cond", "lVal", 
      "number", "unaryOp", "funcRParams", "param", "constExp"
    },
    std::vector<std::string>{
      "", "'const'", "'int'", "'float'", "'void'", "'if'", "'else'", "'while'", 
      "'break'", "'continue'", "'return'", "'+'", "'-'", "'*'", "'/'", "'%'", 
      "'='", "'=='", "'!='", "'<'", "'>'", "'<='", "'>='", "'!'", "'&&'", 
      "'||'", "'('", "')'", "'{'", "'}'", "'['", "']'", "','", "';'"
    },
    std::vector<std::string>{
      "", "CONST", "INT", "FLOAT", "VOID", "IF", "ELSE", "WHILE", "BREAK", 
      "CONTINUE", "RETURN", "PLUS", "MINUS", "MUL", "DIV", "MOD", "ASSIGN", 
      "EQ", "NEQ", "LT", "GT", "LE", "GE", "NOT", "AND", "OR", "L_PAREN", 
      "R_PAREN", "L_BRACE", "R_BRACE", "L_BRACKT", "R_BRACKT", "COMMA", 
      "SEMICOLON", "IDENT", "WS", "LINE_COMMENT", "MULTILINE_COMMENT", "FLOAT_CONST", 
      "INTEGER_CONST"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,310,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,1,0,1,1,1,1,4,1,55,8,1,11,1,12,1,
  	56,1,1,1,1,1,2,1,2,3,2,63,8,2,1,3,1,3,1,3,1,3,1,3,5,3,70,8,3,10,3,12,
  	3,73,9,3,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,84,8,5,10,5,12,5,87,
  	9,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,5,6,97,8,6,10,6,12,6,100,9,6,3,6,
  	102,8,6,1,6,3,6,105,8,6,1,7,1,7,1,7,1,7,5,7,111,8,7,10,7,12,7,114,9,7,
  	1,7,1,7,1,8,1,8,1,8,1,8,1,8,5,8,123,8,8,10,8,12,8,126,9,8,1,8,1,8,3,8,
  	130,8,8,1,9,1,9,1,9,1,9,1,9,5,9,137,8,9,10,9,12,9,140,9,9,3,9,142,8,9,
  	1,9,3,9,145,8,9,1,10,1,10,1,10,1,10,3,10,151,8,10,1,10,1,10,1,10,1,11,
  	1,11,1,12,1,12,1,12,5,12,161,8,12,10,12,12,12,164,9,12,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,5,13,174,8,13,10,13,12,13,177,9,13,3,13,179,
  	8,13,1,14,1,14,5,14,183,8,14,10,14,12,14,186,9,14,1,14,1,14,1,15,1,15,
  	3,15,192,8,15,1,16,1,16,1,16,1,16,1,16,1,16,3,16,200,8,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,230,8,
  	16,1,16,3,16,233,8,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,3,17,245,8,17,1,17,1,17,1,17,1,17,3,17,251,8,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,5,17,259,8,17,10,17,12,17,262,9,17,1,18,1,18,1,18,1,18,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,5,18,279,8,18,10,18,
  	12,18,282,9,18,1,19,1,19,1,19,1,19,1,19,5,19,289,8,19,10,19,12,19,292,
  	9,19,1,20,1,20,1,21,1,21,1,22,1,22,1,22,5,22,301,8,22,10,22,12,22,304,
  	9,22,1,23,1,23,1,24,1,24,1,24,0,2,34,36,25,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,32,34,36,38,40,42,44,46,48,0,8,1,0,2,3,1,0,2,4,1,0,13,
  	15,1,0,11,12,1,0,19,22,1,0,17,18,1,0,38,39,2,0,11,12,23,23,327,0,50,1,
  	0,0,0,2,54,1,0,0,0,4,62,1,0,0,0,6,64,1,0,0,0,8,76,1,0,0,0,10,78,1,0,0,
  	0,12,104,1,0,0,0,14,106,1,0,0,0,16,117,1,0,0,0,18,144,1,0,0,0,20,146,
  	1,0,0,0,22,155,1,0,0,0,24,157,1,0,0,0,26,165,1,0,0,0,28,180,1,0,0,0,30,
  	191,1,0,0,0,32,232,1,0,0,0,34,250,1,0,0,0,36,263,1,0,0,0,38,283,1,0,0,
  	0,40,293,1,0,0,0,42,295,1,0,0,0,44,297,1,0,0,0,46,305,1,0,0,0,48,307,
  	1,0,0,0,50,51,3,2,1,0,51,1,1,0,0,0,52,55,3,20,10,0,53,55,3,4,2,0,54,52,
  	1,0,0,0,54,53,1,0,0,0,55,56,1,0,0,0,56,54,1,0,0,0,56,57,1,0,0,0,57,58,
  	1,0,0,0,58,59,5,0,0,1,59,3,1,0,0,0,60,63,3,6,3,0,61,63,3,14,7,0,62,60,
  	1,0,0,0,62,61,1,0,0,0,63,5,1,0,0,0,64,65,5,1,0,0,65,66,3,8,4,0,66,71,
  	3,10,5,0,67,68,5,32,0,0,68,70,3,10,5,0,69,67,1,0,0,0,70,73,1,0,0,0,71,
  	69,1,0,0,0,71,72,1,0,0,0,72,74,1,0,0,0,73,71,1,0,0,0,74,75,5,33,0,0,75,
  	7,1,0,0,0,76,77,7,0,0,0,77,9,1,0,0,0,78,85,5,34,0,0,79,80,5,30,0,0,80,
  	81,3,48,24,0,81,82,5,31,0,0,82,84,1,0,0,0,83,79,1,0,0,0,84,87,1,0,0,0,
  	85,83,1,0,0,0,85,86,1,0,0,0,86,88,1,0,0,0,87,85,1,0,0,0,88,89,5,16,0,
  	0,89,90,3,12,6,0,90,11,1,0,0,0,91,105,3,48,24,0,92,101,5,28,0,0,93,98,
  	3,12,6,0,94,95,5,32,0,0,95,97,3,12,6,0,96,94,1,0,0,0,97,100,1,0,0,0,98,
  	96,1,0,0,0,98,99,1,0,0,0,99,102,1,0,0,0,100,98,1,0,0,0,101,93,1,0,0,0,
  	101,102,1,0,0,0,102,103,1,0,0,0,103,105,5,29,0,0,104,91,1,0,0,0,104,92,
  	1,0,0,0,105,13,1,0,0,0,106,107,3,8,4,0,107,112,3,16,8,0,108,109,5,32,
  	0,0,109,111,3,16,8,0,110,108,1,0,0,0,111,114,1,0,0,0,112,110,1,0,0,0,
  	112,113,1,0,0,0,113,115,1,0,0,0,114,112,1,0,0,0,115,116,5,33,0,0,116,
  	15,1,0,0,0,117,124,5,34,0,0,118,119,5,30,0,0,119,120,3,48,24,0,120,121,
  	5,31,0,0,121,123,1,0,0,0,122,118,1,0,0,0,123,126,1,0,0,0,124,122,1,0,
  	0,0,124,125,1,0,0,0,125,129,1,0,0,0,126,124,1,0,0,0,127,128,5,16,0,0,
  	128,130,3,18,9,0,129,127,1,0,0,0,129,130,1,0,0,0,130,17,1,0,0,0,131,145,
  	3,34,17,0,132,141,5,28,0,0,133,138,3,18,9,0,134,135,5,32,0,0,135,137,
  	3,18,9,0,136,134,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,138,139,1,0,
  	0,0,139,142,1,0,0,0,140,138,1,0,0,0,141,133,1,0,0,0,141,142,1,0,0,0,142,
  	143,1,0,0,0,143,145,5,29,0,0,144,131,1,0,0,0,144,132,1,0,0,0,145,19,1,
  	0,0,0,146,147,3,22,11,0,147,148,5,34,0,0,148,150,5,26,0,0,149,151,3,24,
  	12,0,150,149,1,0,0,0,150,151,1,0,0,0,151,152,1,0,0,0,152,153,5,27,0,0,
  	153,154,3,28,14,0,154,21,1,0,0,0,155,156,7,1,0,0,156,23,1,0,0,0,157,162,
  	3,26,13,0,158,159,5,32,0,0,159,161,3,26,13,0,160,158,1,0,0,0,161,164,
  	1,0,0,0,162,160,1,0,0,0,162,163,1,0,0,0,163,25,1,0,0,0,164,162,1,0,0,
  	0,165,166,3,8,4,0,166,178,5,34,0,0,167,168,5,30,0,0,168,175,5,31,0,0,
  	169,170,5,30,0,0,170,171,3,34,17,0,171,172,5,31,0,0,172,174,1,0,0,0,173,
  	169,1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,0,175,176,1,0,0,0,176,179,1,
  	0,0,0,177,175,1,0,0,0,178,167,1,0,0,0,178,179,1,0,0,0,179,27,1,0,0,0,
  	180,184,5,28,0,0,181,183,3,30,15,0,182,181,1,0,0,0,183,186,1,0,0,0,184,
  	182,1,0,0,0,184,185,1,0,0,0,185,187,1,0,0,0,186,184,1,0,0,0,187,188,5,
  	29,0,0,188,29,1,0,0,0,189,192,3,4,2,0,190,192,3,32,16,0,191,189,1,0,0,
  	0,191,190,1,0,0,0,192,31,1,0,0,0,193,194,3,38,19,0,194,195,5,16,0,0,195,
  	196,3,34,17,0,196,197,5,33,0,0,197,233,1,0,0,0,198,200,3,34,17,0,199,
  	198,1,0,0,0,199,200,1,0,0,0,200,201,1,0,0,0,201,233,5,33,0,0,202,233,
  	3,28,14,0,203,204,5,5,0,0,204,205,5,26,0,0,205,206,3,36,18,0,206,207,
  	5,27,0,0,207,208,3,32,16,0,208,233,1,0,0,0,209,210,5,5,0,0,210,211,5,
  	26,0,0,211,212,3,36,18,0,212,213,5,27,0,0,213,214,3,32,16,0,214,215,5,
  	6,0,0,215,216,3,32,16,0,216,233,1,0,0,0,217,218,5,7,0,0,218,219,5,26,
  	0,0,219,220,3,36,18,0,220,221,5,27,0,0,221,222,3,32,16,0,222,233,1,0,
  	0,0,223,224,5,8,0,0,224,233,5,33,0,0,225,226,5,9,0,0,226,233,5,33,0,0,
  	227,229,5,10,0,0,228,230,3,34,17,0,229,228,1,0,0,0,229,230,1,0,0,0,230,
  	231,1,0,0,0,231,233,5,33,0,0,232,193,1,0,0,0,232,199,1,0,0,0,232,202,
  	1,0,0,0,232,203,1,0,0,0,232,209,1,0,0,0,232,217,1,0,0,0,232,223,1,0,0,
  	0,232,225,1,0,0,0,232,227,1,0,0,0,233,33,1,0,0,0,234,235,6,17,-1,0,235,
  	236,5,26,0,0,236,237,3,34,17,0,237,238,5,27,0,0,238,251,1,0,0,0,239,251,
  	3,38,19,0,240,251,3,40,20,0,241,242,5,34,0,0,242,244,5,26,0,0,243,245,
  	3,44,22,0,244,243,1,0,0,0,244,245,1,0,0,0,245,246,1,0,0,0,246,251,5,27,
  	0,0,247,248,3,42,21,0,248,249,3,34,17,3,249,251,1,0,0,0,250,234,1,0,0,
  	0,250,239,1,0,0,0,250,240,1,0,0,0,250,241,1,0,0,0,250,247,1,0,0,0,251,
  	260,1,0,0,0,252,253,10,2,0,0,253,254,7,2,0,0,254,259,3,34,17,3,255,256,
  	10,1,0,0,256,257,7,3,0,0,257,259,3,34,17,2,258,252,1,0,0,0,258,255,1,
  	0,0,0,259,262,1,0,0,0,260,258,1,0,0,0,260,261,1,0,0,0,261,35,1,0,0,0,
  	262,260,1,0,0,0,263,264,6,18,-1,0,264,265,3,34,17,0,265,280,1,0,0,0,266,
  	267,10,4,0,0,267,268,7,4,0,0,268,279,3,36,18,5,269,270,10,3,0,0,270,271,
  	7,5,0,0,271,279,3,36,18,4,272,273,10,2,0,0,273,274,5,24,0,0,274,279,3,
  	36,18,3,275,276,10,1,0,0,276,277,5,25,0,0,277,279,3,36,18,2,278,266,1,
  	0,0,0,278,269,1,0,0,0,278,272,1,0,0,0,278,275,1,0,0,0,279,282,1,0,0,0,
  	280,278,1,0,0,0,280,281,1,0,0,0,281,37,1,0,0,0,282,280,1,0,0,0,283,290,
  	5,34,0,0,284,285,5,30,0,0,285,286,3,34,17,0,286,287,5,31,0,0,287,289,
  	1,0,0,0,288,284,1,0,0,0,289,292,1,0,0,0,290,288,1,0,0,0,290,291,1,0,0,
  	0,291,39,1,0,0,0,292,290,1,0,0,0,293,294,7,6,0,0,294,41,1,0,0,0,295,296,
  	7,7,0,0,296,43,1,0,0,0,297,302,3,46,23,0,298,299,5,32,0,0,299,301,3,46,
  	23,0,300,298,1,0,0,0,301,304,1,0,0,0,302,300,1,0,0,0,302,303,1,0,0,0,
  	303,45,1,0,0,0,304,302,1,0,0,0,305,306,3,34,17,0,306,47,1,0,0,0,307,308,
  	3,34,17,0,308,49,1,0,0,0,31,54,56,62,71,85,98,101,104,112,124,129,138,
  	141,144,150,162,175,178,184,191,199,229,232,244,250,258,260,278,280,290,
  	302
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  bifangparserParserStaticData = staticData.release();
}

}

BIFANGParser::BIFANGParser(TokenStream *input) : BIFANGParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

BIFANGParser::BIFANGParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  BIFANGParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *bifangparserParserStaticData->atn, bifangparserParserStaticData->decisionToDFA, bifangparserParserStaticData->sharedContextCache, options);
}

BIFANGParser::~BIFANGParser() {
  delete _interpreter;
}

const atn::ATN& BIFANGParser::getATN() const {
  return *bifangparserParserStaticData->atn;
}

std::string BIFANGParser::getGrammarFileName() const {
  return "BIFANGParser.g4";
}

const std::vector<std::string>& BIFANGParser::getRuleNames() const {
  return bifangparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& BIFANGParser::getVocabulary() const {
  return bifangparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView BIFANGParser::getSerializedATN() const {
  return bifangparserParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

BIFANGParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::CompUnitContext* BIFANGParser::ProgramContext::compUnit() {
  return getRuleContext<BIFANGParser::CompUnitContext>(0);
}


size_t BIFANGParser::ProgramContext::getRuleIndex() const {
  return BIFANGParser::RuleProgram;
}

void BIFANGParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void BIFANGParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
    if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any BIFANGParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
    //判断visitor是否是BIFANGParserVisitor类型的实例，其派生类也算其实例
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
      //AbstractParseTreeVisitor的
    return visitor->visitChildren(this);
}

BIFANGParser::ProgramContext* BIFANGParser::program() {
  ProgramContext *_localctx =
          _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, BIFANGParser::RuleProgram);
#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
      exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    compUnit();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompUnitContext ------------------------------------------------------------------

BIFANGParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::CompUnitContext::EOF() {
  return getToken(BIFANGParser::EOF, 0);
}

std::vector<BIFANGParser::FuncDefContext *> BIFANGParser::CompUnitContext::funcDef() {
  return getRuleContexts<BIFANGParser::FuncDefContext>();
}

BIFANGParser::FuncDefContext* BIFANGParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<BIFANGParser::FuncDefContext>(i);
}

std::vector<BIFANGParser::DeclContext *> BIFANGParser::CompUnitContext::decl() {
  return getRuleContexts<BIFANGParser::DeclContext>();
}

BIFANGParser::DeclContext* BIFANGParser::CompUnitContext::decl(size_t i) {
  return getRuleContext<BIFANGParser::DeclContext>(i);
}


size_t BIFANGParser::CompUnitContext::getRuleIndex() const {
  return BIFANGParser::RuleCompUnit;
}

void BIFANGParser::CompUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompUnit(this);
}

void BIFANGParser::CompUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompUnit(this);
}


std::any BIFANGParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
      //向下转型
    if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::CompUnitContext* BIFANGParser::compUnit() {
    CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 2, BIFANGParser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(54); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(54);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(52);
        funcDef();
        break;
      }

      case 2: {
        setState(53);
        decl();
        break;
      }

      default:
        break;
      }
      setState(56); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30) != 0));
    setState(58);
    match(BIFANGParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

BIFANGParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::ConstDeclContext* BIFANGParser::DeclContext::constDecl() {
  return getRuleContext<BIFANGParser::ConstDeclContext>(0);
}

BIFANGParser::VarDeclContext* BIFANGParser::DeclContext::varDecl() {
  return getRuleContext<BIFANGParser::VarDeclContext>(0);
}


size_t BIFANGParser::DeclContext::getRuleIndex() const {
  return BIFANGParser::RuleDecl;
}

void BIFANGParser::DeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecl(this);
}

void BIFANGParser::DeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecl(this);
}


std::any BIFANGParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::DeclContext* BIFANGParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 4, BIFANGParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(62);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BIFANGParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(60);
        constDecl();
        break;
      }

      case BIFANGParser::INT:
      case BIFANGParser::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(61);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

BIFANGParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::ConstDeclContext::CONST() {
  return getToken(BIFANGParser::CONST, 0);
}

BIFANGParser::BTypeContext* BIFANGParser::ConstDeclContext::bType() {
  return getRuleContext<BIFANGParser::BTypeContext>(0);
}

std::vector<BIFANGParser::ConstDefContext *> BIFANGParser::ConstDeclContext::constDef() {
  return getRuleContexts<BIFANGParser::ConstDefContext>();
}

BIFANGParser::ConstDefContext* BIFANGParser::ConstDeclContext::constDef(size_t i) {
  return getRuleContext<BIFANGParser::ConstDefContext>(i);
}

tree::TerminalNode* BIFANGParser::ConstDeclContext::SEMICOLON() {
  return getToken(BIFANGParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> BIFANGParser::ConstDeclContext::COMMA() {
  return getTokens(BIFANGParser::COMMA);
}

tree::TerminalNode* BIFANGParser::ConstDeclContext::COMMA(size_t i) {
  return getToken(BIFANGParser::COMMA, i);
}


size_t BIFANGParser::ConstDeclContext::getRuleIndex() const {
  return BIFANGParser::RuleConstDecl;
}

void BIFANGParser::ConstDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDecl(this);
}

void BIFANGParser::ConstDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDecl(this);
}


std::any BIFANGParser::ConstDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitConstDecl(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::ConstDeclContext* BIFANGParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, BIFANGParser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    match(BIFANGParser::CONST);
    setState(65);
    bType();
    setState(66);
    constDef();
    setState(71);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BIFANGParser::COMMA) {
      setState(67);
      match(BIFANGParser::COMMA);
      setState(68);
      constDef();
      setState(73);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(74);
    match(BIFANGParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BTypeContext ------------------------------------------------------------------

BIFANGParser::BTypeContext::BTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::BTypeContext::INT() {
  return getToken(BIFANGParser::INT, 0);
}

tree::TerminalNode* BIFANGParser::BTypeContext::FLOAT() {
  return getToken(BIFANGParser::FLOAT, 0);
}


size_t BIFANGParser::BTypeContext::getRuleIndex() const {
  return BIFANGParser::RuleBType;
}

void BIFANGParser::BTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBType(this);
}

void BIFANGParser::BTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBType(this);
}


std::any BIFANGParser::BTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitBType(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::BTypeContext* BIFANGParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 8, BIFANGParser::RuleBType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    _la = _input->LA(1);
    if (!(_la == BIFANGParser::INT

    || _la == BIFANGParser::FLOAT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

BIFANGParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::ConstDefContext::IDENT() {
  return getToken(BIFANGParser::IDENT, 0);
}

tree::TerminalNode* BIFANGParser::ConstDefContext::ASSIGN() {
  return getToken(BIFANGParser::ASSIGN, 0);
}

BIFANGParser::ConstInitValContext* BIFANGParser::ConstDefContext::constInitVal() {
  return getRuleContext<BIFANGParser::ConstInitValContext>(0);
}

std::vector<tree::TerminalNode *> BIFANGParser::ConstDefContext::L_BRACKT() {
  return getTokens(BIFANGParser::L_BRACKT);
}

tree::TerminalNode* BIFANGParser::ConstDefContext::L_BRACKT(size_t i) {
  return getToken(BIFANGParser::L_BRACKT, i);
}

std::vector<BIFANGParser::ConstExpContext *> BIFANGParser::ConstDefContext::constExp() {
  return getRuleContexts<BIFANGParser::ConstExpContext>();
}

BIFANGParser::ConstExpContext* BIFANGParser::ConstDefContext::constExp(size_t i) {
  return getRuleContext<BIFANGParser::ConstExpContext>(i);
}

std::vector<tree::TerminalNode *> BIFANGParser::ConstDefContext::R_BRACKT() {
  return getTokens(BIFANGParser::R_BRACKT);
}

tree::TerminalNode* BIFANGParser::ConstDefContext::R_BRACKT(size_t i) {
  return getToken(BIFANGParser::R_BRACKT, i);
}


size_t BIFANGParser::ConstDefContext::getRuleIndex() const {
  return BIFANGParser::RuleConstDef;
}

void BIFANGParser::ConstDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDef(this);
}

void BIFANGParser::ConstDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDef(this);
}


std::any BIFANGParser::ConstDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitConstDef(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::ConstDefContext* BIFANGParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 10, BIFANGParser::RuleConstDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(BIFANGParser::IDENT);
    setState(85);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BIFANGParser::L_BRACKT) {
      setState(79);
      match(BIFANGParser::L_BRACKT);
      setState(80);
      constExp();
      setState(81);
      match(BIFANGParser::R_BRACKT);
      setState(87);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(88);
    match(BIFANGParser::ASSIGN);
    setState(89);
    constInitVal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

BIFANGParser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::ConstExpContext* BIFANGParser::ConstInitValContext::constExp() {
  return getRuleContext<BIFANGParser::ConstExpContext>(0);
}

tree::TerminalNode* BIFANGParser::ConstInitValContext::L_BRACE() {
  return getToken(BIFANGParser::L_BRACE, 0);
}

tree::TerminalNode* BIFANGParser::ConstInitValContext::R_BRACE() {
  return getToken(BIFANGParser::R_BRACE, 0);
}

std::vector<BIFANGParser::ConstInitValContext *> BIFANGParser::ConstInitValContext::constInitVal() {
  return getRuleContexts<BIFANGParser::ConstInitValContext>();
}

BIFANGParser::ConstInitValContext* BIFANGParser::ConstInitValContext::constInitVal(size_t i) {
  return getRuleContext<BIFANGParser::ConstInitValContext>(i);
}

std::vector<tree::TerminalNode *> BIFANGParser::ConstInitValContext::COMMA() {
  return getTokens(BIFANGParser::COMMA);
}

tree::TerminalNode* BIFANGParser::ConstInitValContext::COMMA(size_t i) {
  return getToken(BIFANGParser::COMMA, i);
}


size_t BIFANGParser::ConstInitValContext::getRuleIndex() const {
  return BIFANGParser::RuleConstInitVal;
}

void BIFANGParser::ConstInitValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstInitVal(this);
}

void BIFANGParser::ConstInitValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstInitVal(this);
}


std::any BIFANGParser::ConstInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitConstInitVal(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::ConstInitValContext* BIFANGParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 12, BIFANGParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(104);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BIFANGParser::PLUS:
      case BIFANGParser::MINUS:
      case BIFANGParser::NOT:
      case BIFANGParser::L_PAREN:
      case BIFANGParser::IDENT:
      case BIFANGParser::FLOAT_CONST:
      case BIFANGParser::INTEGER_CONST: {
        enterOuterAlt(_localctx, 1);
        setState(91);
        constExp();
        break;
      }

      case BIFANGParser::L_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(92);
        match(BIFANGParser::L_BRACE);
        setState(101);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 842157529088) != 0)) {
          setState(93);
          constInitVal();
          setState(98);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == BIFANGParser::COMMA) {
            setState(94);
            match(BIFANGParser::COMMA);
            setState(95);
            constInitVal();
            setState(100);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(103);
        match(BIFANGParser::R_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

BIFANGParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::BTypeContext* BIFANGParser::VarDeclContext::bType() {
  return getRuleContext<BIFANGParser::BTypeContext>(0);
}

std::vector<BIFANGParser::VarDefContext *> BIFANGParser::VarDeclContext::varDef() {
  return getRuleContexts<BIFANGParser::VarDefContext>();
}

BIFANGParser::VarDefContext* BIFANGParser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<BIFANGParser::VarDefContext>(i);
}

tree::TerminalNode* BIFANGParser::VarDeclContext::SEMICOLON() {
  return getToken(BIFANGParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> BIFANGParser::VarDeclContext::COMMA() {
  return getTokens(BIFANGParser::COMMA);
}

tree::TerminalNode* BIFANGParser::VarDeclContext::COMMA(size_t i) {
  return getToken(BIFANGParser::COMMA, i);
}


size_t BIFANGParser::VarDeclContext::getRuleIndex() const {
  return BIFANGParser::RuleVarDecl;
}

void BIFANGParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void BIFANGParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}


std::any BIFANGParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::VarDeclContext* BIFANGParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 14, BIFANGParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    bType();
    setState(107);
    varDef();
    setState(112);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BIFANGParser::COMMA) {
      setState(108);
      match(BIFANGParser::COMMA);
      setState(109);
      varDef();
      setState(114);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(115);
    match(BIFANGParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

BIFANGParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::VarDefContext::IDENT() {
  return getToken(BIFANGParser::IDENT, 0);
}

std::vector<tree::TerminalNode *> BIFANGParser::VarDefContext::L_BRACKT() {
  return getTokens(BIFANGParser::L_BRACKT);
}

tree::TerminalNode* BIFANGParser::VarDefContext::L_BRACKT(size_t i) {
  return getToken(BIFANGParser::L_BRACKT, i);
}

std::vector<BIFANGParser::ConstExpContext *> BIFANGParser::VarDefContext::constExp() {
  return getRuleContexts<BIFANGParser::ConstExpContext>();
}

BIFANGParser::ConstExpContext* BIFANGParser::VarDefContext::constExp(size_t i) {
  return getRuleContext<BIFANGParser::ConstExpContext>(i);
}

std::vector<tree::TerminalNode *> BIFANGParser::VarDefContext::R_BRACKT() {
  return getTokens(BIFANGParser::R_BRACKT);
}

tree::TerminalNode* BIFANGParser::VarDefContext::R_BRACKT(size_t i) {
  return getToken(BIFANGParser::R_BRACKT, i);
}

tree::TerminalNode* BIFANGParser::VarDefContext::ASSIGN() {
  return getToken(BIFANGParser::ASSIGN, 0);
}

BIFANGParser::InitValContext* BIFANGParser::VarDefContext::initVal() {
  return getRuleContext<BIFANGParser::InitValContext>(0);
}


size_t BIFANGParser::VarDefContext::getRuleIndex() const {
  return BIFANGParser::RuleVarDef;
}

void BIFANGParser::VarDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDef(this);
}

void BIFANGParser::VarDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDef(this);
}


std::any BIFANGParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::VarDefContext* BIFANGParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 16, BIFANGParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    match(BIFANGParser::IDENT);
    setState(124);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BIFANGParser::L_BRACKT) {
      setState(118);
      match(BIFANGParser::L_BRACKT);
      setState(119);
      constExp();
      setState(120);
      match(BIFANGParser::R_BRACKT);
      setState(126);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(129);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BIFANGParser::ASSIGN) {
      setState(127);
      match(BIFANGParser::ASSIGN);
      setState(128);
      initVal();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitValContext ------------------------------------------------------------------

BIFANGParser::InitValContext::InitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::ExpContext* BIFANGParser::InitValContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}

tree::TerminalNode* BIFANGParser::InitValContext::L_BRACE() {
  return getToken(BIFANGParser::L_BRACE, 0);
}

tree::TerminalNode* BIFANGParser::InitValContext::R_BRACE() {
  return getToken(BIFANGParser::R_BRACE, 0);
}

std::vector<BIFANGParser::InitValContext *> BIFANGParser::InitValContext::initVal() {
  return getRuleContexts<BIFANGParser::InitValContext>();
}

BIFANGParser::InitValContext* BIFANGParser::InitValContext::initVal(size_t i) {
  return getRuleContext<BIFANGParser::InitValContext>(i);
}

std::vector<tree::TerminalNode *> BIFANGParser::InitValContext::COMMA() {
  return getTokens(BIFANGParser::COMMA);
}

tree::TerminalNode* BIFANGParser::InitValContext::COMMA(size_t i) {
  return getToken(BIFANGParser::COMMA, i);
}


size_t BIFANGParser::InitValContext::getRuleIndex() const {
  return BIFANGParser::RuleInitVal;
}

void BIFANGParser::InitValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitVal(this);
}

void BIFANGParser::InitValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitVal(this);
}


std::any BIFANGParser::InitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitInitVal(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::InitValContext* BIFANGParser::initVal() {
  InitValContext *_localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
  enterRule(_localctx, 18, BIFANGParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(144);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BIFANGParser::PLUS:
      case BIFANGParser::MINUS:
      case BIFANGParser::NOT:
      case BIFANGParser::L_PAREN:
      case BIFANGParser::IDENT:
      case BIFANGParser::FLOAT_CONST:
      case BIFANGParser::INTEGER_CONST: {
        enterOuterAlt(_localctx, 1);
        setState(131);
        exp(0);
        break;
      }

      case BIFANGParser::L_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(132);
        match(BIFANGParser::L_BRACE);
        setState(141);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 842157529088) != 0)) {
          setState(133);
          initVal();
          setState(138);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == BIFANGParser::COMMA) {
            setState(134);
            match(BIFANGParser::COMMA);
            setState(135);
            initVal();
            setState(140);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(143);
        match(BIFANGParser::R_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

BIFANGParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::FuncTypeContext* BIFANGParser::FuncDefContext::funcType() {
  return getRuleContext<BIFANGParser::FuncTypeContext>(0);
}

tree::TerminalNode* BIFANGParser::FuncDefContext::IDENT() {
  return getToken(BIFANGParser::IDENT, 0);
}

tree::TerminalNode* BIFANGParser::FuncDefContext::L_PAREN() {
  return getToken(BIFANGParser::L_PAREN, 0);
}

tree::TerminalNode* BIFANGParser::FuncDefContext::R_PAREN() {
  return getToken(BIFANGParser::R_PAREN, 0);
}

BIFANGParser::BlockContext* BIFANGParser::FuncDefContext::block() {
  return getRuleContext<BIFANGParser::BlockContext>(0);
}

BIFANGParser::FuncFParamsContext* BIFANGParser::FuncDefContext::funcFParams() {
  return getRuleContext<BIFANGParser::FuncFParamsContext>(0);
}


size_t BIFANGParser::FuncDefContext::getRuleIndex() const {
  return BIFANGParser::RuleFuncDef;
}

void BIFANGParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void BIFANGParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}


std::any BIFANGParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::FuncDefContext* BIFANGParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 20, BIFANGParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    funcType();
    setState(147);
    match(BIFANGParser::IDENT);
    setState(148);
    match(BIFANGParser::L_PAREN);
    setState(150);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BIFANGParser::INT

    || _la == BIFANGParser::FLOAT) {
      setState(149);
      funcFParams();
    }
    setState(152);
    match(BIFANGParser::R_PAREN);
    setState(153);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

BIFANGParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::FuncTypeContext::VOID() {
  return getToken(BIFANGParser::VOID, 0);
}

tree::TerminalNode* BIFANGParser::FuncTypeContext::INT() {
  return getToken(BIFANGParser::INT, 0);
}

tree::TerminalNode* BIFANGParser::FuncTypeContext::FLOAT() {
  return getToken(BIFANGParser::FLOAT, 0);
}


size_t BIFANGParser::FuncTypeContext::getRuleIndex() const {
  return BIFANGParser::RuleFuncType;
}

void BIFANGParser::FuncTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncType(this);
}

void BIFANGParser::FuncTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncType(this);
}


std::any BIFANGParser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::FuncTypeContext* BIFANGParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 22, BIFANGParser::RuleFuncType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamsContext ------------------------------------------------------------------

BIFANGParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BIFANGParser::FuncFParamContext *> BIFANGParser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<BIFANGParser::FuncFParamContext>();
}

BIFANGParser::FuncFParamContext* BIFANGParser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<BIFANGParser::FuncFParamContext>(i);
}

std::vector<tree::TerminalNode *> BIFANGParser::FuncFParamsContext::COMMA() {
  return getTokens(BIFANGParser::COMMA);
}

tree::TerminalNode* BIFANGParser::FuncFParamsContext::COMMA(size_t i) {
  return getToken(BIFANGParser::COMMA, i);
}


size_t BIFANGParser::FuncFParamsContext::getRuleIndex() const {
  return BIFANGParser::RuleFuncFParams;
}

void BIFANGParser::FuncFParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncFParams(this);
}

void BIFANGParser::FuncFParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncFParams(this);
}


std::any BIFANGParser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::FuncFParamsContext* BIFANGParser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 24, BIFANGParser::RuleFuncFParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    funcFParam();
    setState(162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BIFANGParser::COMMA) {
      setState(158);
      match(BIFANGParser::COMMA);
      setState(159);
      funcFParam();
      setState(164);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

BIFANGParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::BTypeContext* BIFANGParser::FuncFParamContext::bType() {
  return getRuleContext<BIFANGParser::BTypeContext>(0);
}

tree::TerminalNode* BIFANGParser::FuncFParamContext::IDENT() {
  return getToken(BIFANGParser::IDENT, 0);
}

std::vector<tree::TerminalNode *> BIFANGParser::FuncFParamContext::L_BRACKT() {
  return getTokens(BIFANGParser::L_BRACKT);
}

tree::TerminalNode* BIFANGParser::FuncFParamContext::L_BRACKT(size_t i) {
  return getToken(BIFANGParser::L_BRACKT, i);
}

std::vector<tree::TerminalNode *> BIFANGParser::FuncFParamContext::R_BRACKT() {
  return getTokens(BIFANGParser::R_BRACKT);
}

tree::TerminalNode* BIFANGParser::FuncFParamContext::R_BRACKT(size_t i) {
  return getToken(BIFANGParser::R_BRACKT, i);
}

std::vector<BIFANGParser::ExpContext *> BIFANGParser::FuncFParamContext::exp() {
  return getRuleContexts<BIFANGParser::ExpContext>();
}

BIFANGParser::ExpContext* BIFANGParser::FuncFParamContext::exp(size_t i) {
  return getRuleContext<BIFANGParser::ExpContext>(i);
}


size_t BIFANGParser::FuncFParamContext::getRuleIndex() const {
  return BIFANGParser::RuleFuncFParam;
}

void BIFANGParser::FuncFParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncFParam(this);
}

void BIFANGParser::FuncFParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncFParam(this);
}


std::any BIFANGParser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::FuncFParamContext* BIFANGParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 26, BIFANGParser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(165);
    bType();
    setState(166);
    match(BIFANGParser::IDENT);
    setState(178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BIFANGParser::L_BRACKT) {
      setState(167);
      match(BIFANGParser::L_BRACKT);
      setState(168);
      match(BIFANGParser::R_BRACKT);
      setState(175);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BIFANGParser::L_BRACKT) {
        setState(169);
        match(BIFANGParser::L_BRACKT);
        setState(170);
        exp(0);
        setState(171);
        match(BIFANGParser::R_BRACKT);
        setState(177);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

BIFANGParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::BlockContext::L_BRACE() {
  return getToken(BIFANGParser::L_BRACE, 0);
}

tree::TerminalNode* BIFANGParser::BlockContext::R_BRACE() {
  return getToken(BIFANGParser::R_BRACE, 0);
}

std::vector<BIFANGParser::BlockItemContext *> BIFANGParser::BlockContext::blockItem() {
  return getRuleContexts<BIFANGParser::BlockItemContext>();
}

BIFANGParser::BlockItemContext* BIFANGParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<BIFANGParser::BlockItemContext>(i);
}


size_t BIFANGParser::BlockContext::getRuleIndex() const {
  return BIFANGParser::RuleBlock;
}

void BIFANGParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void BIFANGParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any BIFANGParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::BlockContext* BIFANGParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 28, BIFANGParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    match(BIFANGParser::L_BRACE);
    setState(184);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 850747465646) != 0)) {
      setState(181);
      blockItem();
      setState(186);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(187);
    match(BIFANGParser::R_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

BIFANGParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::DeclContext* BIFANGParser::BlockItemContext::decl() {
  return getRuleContext<BIFANGParser::DeclContext>(0);
}

BIFANGParser::StmtContext* BIFANGParser::BlockItemContext::stmt() {
  return getRuleContext<BIFANGParser::StmtContext>(0);
}


size_t BIFANGParser::BlockItemContext::getRuleIndex() const {
  return BIFANGParser::RuleBlockItem;
}

void BIFANGParser::BlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockItem(this);
}

void BIFANGParser::BlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockItem(this);
}


std::any BIFANGParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::BlockItemContext* BIFANGParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 30, BIFANGParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(191);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BIFANGParser::CONST:
      case BIFANGParser::INT:
      case BIFANGParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(189);
        decl();
        break;
      }

      case BIFANGParser::IF:
      case BIFANGParser::WHILE:
      case BIFANGParser::BREAK:
      case BIFANGParser::CONTINUE:
      case BIFANGParser::RETURN:
      case BIFANGParser::PLUS:
      case BIFANGParser::MINUS:
      case BIFANGParser::NOT:
      case BIFANGParser::L_PAREN:
      case BIFANGParser::L_BRACE:
      case BIFANGParser::SEMICOLON:
      case BIFANGParser::IDENT:
      case BIFANGParser::FLOAT_CONST:
      case BIFANGParser::INTEGER_CONST: {
        enterOuterAlt(_localctx, 2);
        setState(190);
        stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

BIFANGParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BIFANGParser::StmtContext::getRuleIndex() const {
  return BIFANGParser::RuleStmt;
}

void BIFANGParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- WhileStmtContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::WhileStmtContext::WHILE() {
  return getToken(BIFANGParser::WHILE, 0);
}

tree::TerminalNode* BIFANGParser::WhileStmtContext::L_PAREN() {
  return getToken(BIFANGParser::L_PAREN, 0);
}

BIFANGParser::CondContext* BIFANGParser::WhileStmtContext::cond() {
  return getRuleContext<BIFANGParser::CondContext>(0);
}

tree::TerminalNode* BIFANGParser::WhileStmtContext::R_PAREN() {
  return getToken(BIFANGParser::R_PAREN, 0);
}

BIFANGParser::StmtContext* BIFANGParser::WhileStmtContext::stmt() {
  return getRuleContext<BIFANGParser::StmtContext>(0);
}

BIFANGParser::WhileStmtContext::WhileStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::WhileStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStmt(this);
}
void BIFANGParser::WhileStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStmt(this);
}

std::any BIFANGParser::WhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitWhileStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStmtContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::IfStmtContext::IF() {
  return getToken(BIFANGParser::IF, 0);
}

tree::TerminalNode* BIFANGParser::IfStmtContext::L_PAREN() {
  return getToken(BIFANGParser::L_PAREN, 0);
}

BIFANGParser::CondContext* BIFANGParser::IfStmtContext::cond() {
  return getRuleContext<BIFANGParser::CondContext>(0);
}

tree::TerminalNode* BIFANGParser::IfStmtContext::R_PAREN() {
  return getToken(BIFANGParser::R_PAREN, 0);
}

BIFANGParser::StmtContext* BIFANGParser::IfStmtContext::stmt() {
  return getRuleContext<BIFANGParser::StmtContext>(0);
}

BIFANGParser::IfStmtContext::IfStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}
void BIFANGParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}

std::any BIFANGParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStmtContext ------------------------------------------------------------------

BIFANGParser::BlockContext* BIFANGParser::BlockStmtContext::block() {
  return getRuleContext<BIFANGParser::BlockContext>(0);
}

BIFANGParser::BlockStmtContext::BlockStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::BlockStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockStmt(this);
}
void BIFANGParser::BlockStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockStmt(this);
}

std::any BIFANGParser::BlockStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitBlockStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfElseStmtContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::IfElseStmtContext::IF() {
  return getToken(BIFANGParser::IF, 0);
}

tree::TerminalNode* BIFANGParser::IfElseStmtContext::L_PAREN() {
  return getToken(BIFANGParser::L_PAREN, 0);
}

BIFANGParser::CondContext* BIFANGParser::IfElseStmtContext::cond() {
  return getRuleContext<BIFANGParser::CondContext>(0);
}

tree::TerminalNode* BIFANGParser::IfElseStmtContext::R_PAREN() {
  return getToken(BIFANGParser::R_PAREN, 0);
}

std::vector<BIFANGParser::StmtContext *> BIFANGParser::IfElseStmtContext::stmt() {
  return getRuleContexts<BIFANGParser::StmtContext>();
}

BIFANGParser::StmtContext* BIFANGParser::IfElseStmtContext::stmt(size_t i) {
  return getRuleContext<BIFANGParser::StmtContext>(i);
}

tree::TerminalNode* BIFANGParser::IfElseStmtContext::ELSE() {
  return getToken(BIFANGParser::ELSE, 0);
}

BIFANGParser::IfElseStmtContext::IfElseStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::IfElseStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfElseStmt(this);
}
void BIFANGParser::IfElseStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfElseStmt(this);
}

std::any BIFANGParser::IfElseStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitIfElseStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStmtContext ------------------------------------------------------------------

BIFANGParser::LValContext* BIFANGParser::AssignStmtContext::lVal() {
  return getRuleContext<BIFANGParser::LValContext>(0);
}

tree::TerminalNode* BIFANGParser::AssignStmtContext::ASSIGN() {
  return getToken(BIFANGParser::ASSIGN, 0);
}

BIFANGParser::ExpContext* BIFANGParser::AssignStmtContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}

tree::TerminalNode* BIFANGParser::AssignStmtContext::SEMICOLON() {
  return getToken(BIFANGParser::SEMICOLON, 0);
}

BIFANGParser::AssignStmtContext::AssignStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::AssignStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignStmt(this);
}
void BIFANGParser::AssignStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignStmt(this);
}

std::any BIFANGParser::AssignStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitAssignStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStmtContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::BreakStmtContext::BREAK() {
  return getToken(BIFANGParser::BREAK, 0);
}

tree::TerminalNode* BIFANGParser::BreakStmtContext::SEMICOLON() {
  return getToken(BIFANGParser::SEMICOLON, 0);
}

BIFANGParser::BreakStmtContext::BreakStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::BreakStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStmt(this);
}
void BIFANGParser::BreakStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStmt(this);
}

std::any BIFANGParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpStmtContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::ExpStmtContext::SEMICOLON() {
  return getToken(BIFANGParser::SEMICOLON, 0);
}

BIFANGParser::ExpContext* BIFANGParser::ExpStmtContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}

BIFANGParser::ExpStmtContext::ExpStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::ExpStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpStmt(this);
}
void BIFANGParser::ExpStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpStmt(this);
}

std::any BIFANGParser::ExpStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitExpStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStmtContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::ReturnStmtContext::RETURN() {
  return getToken(BIFANGParser::RETURN, 0);
}

tree::TerminalNode* BIFANGParser::ReturnStmtContext::SEMICOLON() {
  return getToken(BIFANGParser::SEMICOLON, 0);
}

BIFANGParser::ExpContext* BIFANGParser::ReturnStmtContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}

BIFANGParser::ReturnStmtContext::ReturnStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::ReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStmt(this);
}
void BIFANGParser::ReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStmt(this);
}

std::any BIFANGParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStmtContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::ContinueStmtContext::CONTINUE() {
  return getToken(BIFANGParser::CONTINUE, 0);
}

tree::TerminalNode* BIFANGParser::ContinueStmtContext::SEMICOLON() {
  return getToken(BIFANGParser::SEMICOLON, 0);
}

BIFANGParser::ContinueStmtContext::ContinueStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void BIFANGParser::ContinueStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStmt(this);
}
void BIFANGParser::ContinueStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStmt(this);
}

std::any BIFANGParser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}
BIFANGParser::StmtContext* BIFANGParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 32, BIFANGParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<BIFANGParser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(193);
      lVal();
      setState(194);
      match(BIFANGParser::ASSIGN);
      setState(195);
      exp(0);
      setState(196);
      match(BIFANGParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<BIFANGParser::ExpStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(199);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 841889093632) != 0)) {
        setState(198);
        exp(0);
      }
      setState(201);
      match(BIFANGParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<BIFANGParser::BlockStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(202);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<BIFANGParser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(203);
      match(BIFANGParser::IF);
      setState(204);
      match(BIFANGParser::L_PAREN);
      setState(205);
      cond(0);
      setState(206);
      match(BIFANGParser::R_PAREN);
      setState(207);
      stmt();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<BIFANGParser::IfElseStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(209);
      match(BIFANGParser::IF);
      setState(210);
      match(BIFANGParser::L_PAREN);
      setState(211);
      cond(0);
      setState(212);
      match(BIFANGParser::R_PAREN);
      setState(213);
      stmt();
      setState(214);
      match(BIFANGParser::ELSE);
      setState(215);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<BIFANGParser::WhileStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(217);
      match(BIFANGParser::WHILE);
      setState(218);
      match(BIFANGParser::L_PAREN);
      setState(219);
      cond(0);
      setState(220);
      match(BIFANGParser::R_PAREN);
      setState(221);
      stmt();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<BIFANGParser::BreakStmtContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(223);
      match(BIFANGParser::BREAK);
      setState(224);
      match(BIFANGParser::SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<BIFANGParser::ContinueStmtContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(225);
      match(BIFANGParser::CONTINUE);
      setState(226);
      match(BIFANGParser::SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BIFANGParser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(227);
      match(BIFANGParser::RETURN);
      setState(229);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 841889093632) != 0)) {
        setState(228);
        exp(0);
      }
      setState(231);
      match(BIFANGParser::SEMICOLON);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

BIFANGParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BIFANGParser::ExpContext::getRuleIndex() const {
  return BIFANGParser::RuleExp;
}

void BIFANGParser::ExpContext::copyFrom(ExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExpParenthesisContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::ExpParenthesisContext::L_PAREN() {
  return getToken(BIFANGParser::L_PAREN, 0);
}

BIFANGParser::ExpContext* BIFANGParser::ExpParenthesisContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}

tree::TerminalNode* BIFANGParser::ExpParenthesisContext::R_PAREN() {
  return getToken(BIFANGParser::R_PAREN, 0);
}

BIFANGParser::ExpParenthesisContext::ExpParenthesisContext(ExpContext *ctx) { copyFrom(ctx); }

void BIFANGParser::ExpParenthesisContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpParenthesis(this);
}
void BIFANGParser::ExpParenthesisContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpParenthesis(this);
}

std::any BIFANGParser::ExpParenthesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitExpParenthesis(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallFuncExpContext ------------------------------------------------------------------

tree::TerminalNode* BIFANGParser::CallFuncExpContext::IDENT() {
  return getToken(BIFANGParser::IDENT, 0);
}

tree::TerminalNode* BIFANGParser::CallFuncExpContext::L_PAREN() {
  return getToken(BIFANGParser::L_PAREN, 0);
}

tree::TerminalNode* BIFANGParser::CallFuncExpContext::R_PAREN() {
  return getToken(BIFANGParser::R_PAREN, 0);
}

BIFANGParser::FuncRParamsContext* BIFANGParser::CallFuncExpContext::funcRParams() {
  return getRuleContext<BIFANGParser::FuncRParamsContext>(0);
}

BIFANGParser::CallFuncExpContext::CallFuncExpContext(ExpContext *ctx) { copyFrom(ctx); }

void BIFANGParser::CallFuncExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallFuncExp(this);
}
void BIFANGParser::CallFuncExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallFuncExp(this);
}

std::any BIFANGParser::CallFuncExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitCallFuncExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LValExpContext ------------------------------------------------------------------

BIFANGParser::LValContext* BIFANGParser::LValExpContext::lVal() {
  return getRuleContext<BIFANGParser::LValContext>(0);
}

BIFANGParser::LValExpContext::LValExpContext(ExpContext *ctx) { copyFrom(ctx); }

void BIFANGParser::LValExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLValExp(this);
}
void BIFANGParser::LValExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLValExp(this);
}

std::any BIFANGParser::LValExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitLValExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberExpContext ------------------------------------------------------------------

BIFANGParser::NumberContext* BIFANGParser::NumberExpContext::number() {
  return getRuleContext<BIFANGParser::NumberContext>(0);
}

BIFANGParser::NumberExpContext::NumberExpContext(ExpContext *ctx) { copyFrom(ctx); }

void BIFANGParser::NumberExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumberExp(this);
}
void BIFANGParser::NumberExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumberExp(this);
}

std::any BIFANGParser::NumberExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitNumberExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryOpExpContext ------------------------------------------------------------------

BIFANGParser::UnaryOpContext* BIFANGParser::UnaryOpExpContext::unaryOp() {
  return getRuleContext<BIFANGParser::UnaryOpContext>(0);
}

BIFANGParser::ExpContext* BIFANGParser::UnaryOpExpContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}

BIFANGParser::UnaryOpExpContext::UnaryOpExpContext(ExpContext *ctx) { copyFrom(ctx); }

void BIFANGParser::UnaryOpExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOpExp(this);
}
void BIFANGParser::UnaryOpExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOpExp(this);
}

std::any BIFANGParser::UnaryOpExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitUnaryOpExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PlusExpContext ------------------------------------------------------------------

std::vector<BIFANGParser::ExpContext *> BIFANGParser::PlusExpContext::exp() {
  return getRuleContexts<BIFANGParser::ExpContext>();
}

BIFANGParser::ExpContext* BIFANGParser::PlusExpContext::exp(size_t i) {
  return getRuleContext<BIFANGParser::ExpContext>(i);
}

tree::TerminalNode* BIFANGParser::PlusExpContext::PLUS() {
  return getToken(BIFANGParser::PLUS, 0);
}

tree::TerminalNode* BIFANGParser::PlusExpContext::MINUS() {
  return getToken(BIFANGParser::MINUS, 0);
}

BIFANGParser::PlusExpContext::PlusExpContext(ExpContext *ctx) { copyFrom(ctx); }

void BIFANGParser::PlusExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlusExp(this);
}
void BIFANGParser::PlusExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlusExp(this);
}

std::any BIFANGParser::PlusExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitPlusExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulExpContext ------------------------------------------------------------------

std::vector<BIFANGParser::ExpContext *> BIFANGParser::MulExpContext::exp() {
  return getRuleContexts<BIFANGParser::ExpContext>();
}

BIFANGParser::ExpContext* BIFANGParser::MulExpContext::exp(size_t i) {
  return getRuleContext<BIFANGParser::ExpContext>(i);
}

tree::TerminalNode* BIFANGParser::MulExpContext::MUL() {
  return getToken(BIFANGParser::MUL, 0);
}

tree::TerminalNode* BIFANGParser::MulExpContext::DIV() {
  return getToken(BIFANGParser::DIV, 0);
}

tree::TerminalNode* BIFANGParser::MulExpContext::MOD() {
  return getToken(BIFANGParser::MOD, 0);
}

BIFANGParser::MulExpContext::MulExpContext(ExpContext *ctx) { copyFrom(ctx); }

void BIFANGParser::MulExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulExp(this);
}
void BIFANGParser::MulExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulExp(this);
}

std::any BIFANGParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::ExpContext* BIFANGParser::exp() {
   return exp(0);
}

BIFANGParser::ExpContext* BIFANGParser::exp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  BIFANGParser::ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, parentState);
  BIFANGParser::ExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, BIFANGParser::RuleExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(250);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ExpParenthesisContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(235);
      match(BIFANGParser::L_PAREN);
      setState(236);
      exp(0);
      setState(237);
      match(BIFANGParser::R_PAREN);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<LValExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(239);
      lVal();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<NumberExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(240);
      number();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<CallFuncExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(241);
      match(BIFANGParser::IDENT);
      setState(242);
      match(BIFANGParser::L_PAREN);
      setState(244);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 841889093632) != 0)) {
        setState(243);
        funcRParams();
      }
      setState(246);
      match(BIFANGParser::R_PAREN);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<UnaryOpExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(247);
      unaryOp();
      setState(248);
      exp(3);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(260);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(258);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulExpContext>(_tracker.createInstance<ExpContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExp);
          setState(252);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(253);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 57344) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(254);
          exp(3);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<PlusExpContext>(_tracker.createInstance<ExpContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExp);
          setState(255);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(256);
          _la = _input->LA(1);
          if (!(_la == BIFANGParser::PLUS

          || _la == BIFANGParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(257);
          exp(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(262);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

BIFANGParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BIFANGParser::CondContext::getRuleIndex() const {
  return BIFANGParser::RuleCond;
}

void BIFANGParser::CondContext::copyFrom(CondContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LtCondContext ------------------------------------------------------------------

std::vector<BIFANGParser::CondContext *> BIFANGParser::LtCondContext::cond() {
  return getRuleContexts<BIFANGParser::CondContext>();
}

BIFANGParser::CondContext* BIFANGParser::LtCondContext::cond(size_t i) {
  return getRuleContext<BIFANGParser::CondContext>(i);
}

tree::TerminalNode* BIFANGParser::LtCondContext::LT() {
  return getToken(BIFANGParser::LT, 0);
}

tree::TerminalNode* BIFANGParser::LtCondContext::GT() {
  return getToken(BIFANGParser::GT, 0);
}

tree::TerminalNode* BIFANGParser::LtCondContext::LE() {
  return getToken(BIFANGParser::LE, 0);
}

tree::TerminalNode* BIFANGParser::LtCondContext::GE() {
  return getToken(BIFANGParser::GE, 0);
}

BIFANGParser::LtCondContext::LtCondContext(CondContext *ctx) { copyFrom(ctx); }

void BIFANGParser::LtCondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLtCond(this);
}
void BIFANGParser::LtCondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLtCond(this);
}

std::any BIFANGParser::LtCondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitLtCond(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrCondContext ------------------------------------------------------------------

std::vector<BIFANGParser::CondContext *> BIFANGParser::OrCondContext::cond() {
  return getRuleContexts<BIFANGParser::CondContext>();
}

BIFANGParser::CondContext* BIFANGParser::OrCondContext::cond(size_t i) {
  return getRuleContext<BIFANGParser::CondContext>(i);
}

tree::TerminalNode* BIFANGParser::OrCondContext::OR() {
  return getToken(BIFANGParser::OR, 0);
}

BIFANGParser::OrCondContext::OrCondContext(CondContext *ctx) { copyFrom(ctx); }

void BIFANGParser::OrCondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrCond(this);
}
void BIFANGParser::OrCondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrCond(this);
}

std::any BIFANGParser::OrCondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitOrCond(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpCondContext ------------------------------------------------------------------

BIFANGParser::ExpContext* BIFANGParser::ExpCondContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}

BIFANGParser::ExpCondContext::ExpCondContext(CondContext *ctx) { copyFrom(ctx); }

void BIFANGParser::ExpCondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpCond(this);
}
void BIFANGParser::ExpCondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpCond(this);
}

std::any BIFANGParser::ExpCondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitExpCond(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndCondContext ------------------------------------------------------------------

std::vector<BIFANGParser::CondContext *> BIFANGParser::AndCondContext::cond() {
  return getRuleContexts<BIFANGParser::CondContext>();
}

BIFANGParser::CondContext* BIFANGParser::AndCondContext::cond(size_t i) {
  return getRuleContext<BIFANGParser::CondContext>(i);
}

tree::TerminalNode* BIFANGParser::AndCondContext::AND() {
  return getToken(BIFANGParser::AND, 0);
}

BIFANGParser::AndCondContext::AndCondContext(CondContext *ctx) { copyFrom(ctx); }

void BIFANGParser::AndCondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndCond(this);
}
void BIFANGParser::AndCondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndCond(this);
}

std::any BIFANGParser::AndCondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitAndCond(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EqCondContext ------------------------------------------------------------------

std::vector<BIFANGParser::CondContext *> BIFANGParser::EqCondContext::cond() {
  return getRuleContexts<BIFANGParser::CondContext>();
}

BIFANGParser::CondContext* BIFANGParser::EqCondContext::cond(size_t i) {
  return getRuleContext<BIFANGParser::CondContext>(i);
}

tree::TerminalNode* BIFANGParser::EqCondContext::EQ() {
  return getToken(BIFANGParser::EQ, 0);
}

tree::TerminalNode* BIFANGParser::EqCondContext::NEQ() {
  return getToken(BIFANGParser::NEQ, 0);
}

BIFANGParser::EqCondContext::EqCondContext(CondContext *ctx) { copyFrom(ctx); }

void BIFANGParser::EqCondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqCond(this);
}
void BIFANGParser::EqCondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqCond(this);
}

std::any BIFANGParser::EqCondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitEqCond(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::CondContext* BIFANGParser::cond() {
   return cond(0);
}

BIFANGParser::CondContext* BIFANGParser::cond(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  BIFANGParser::CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, parentState);
  BIFANGParser::CondContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, BIFANGParser::RuleCond, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ExpCondContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(264);
    exp(0);
    _ctx->stop = _input->LT(-1);
    setState(280);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(278);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<LtCondContext>(_tracker.createInstance<CondContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCond);
          setState(266);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(267);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7864320) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(268);
          cond(5);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<EqCondContext>(_tracker.createInstance<CondContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCond);
          setState(269);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(270);
          _la = _input->LA(1);
          if (!(_la == BIFANGParser::EQ

          || _la == BIFANGParser::NEQ)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(271);
          cond(4);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<AndCondContext>(_tracker.createInstance<CondContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCond);
          setState(272);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(273);
          match(BIFANGParser::AND);
          setState(274);
          cond(3);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<OrCondContext>(_tracker.createInstance<CondContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCond);
          setState(275);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(276);
          match(BIFANGParser::OR);
          setState(277);
          cond(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(282);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

BIFANGParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::LValContext::IDENT() {
  return getToken(BIFANGParser::IDENT, 0);
}

std::vector<tree::TerminalNode *> BIFANGParser::LValContext::L_BRACKT() {
  return getTokens(BIFANGParser::L_BRACKT);
}

tree::TerminalNode* BIFANGParser::LValContext::L_BRACKT(size_t i) {
  return getToken(BIFANGParser::L_BRACKT, i);
}

std::vector<BIFANGParser::ExpContext *> BIFANGParser::LValContext::exp() {
  return getRuleContexts<BIFANGParser::ExpContext>();
}

BIFANGParser::ExpContext* BIFANGParser::LValContext::exp(size_t i) {
  return getRuleContext<BIFANGParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> BIFANGParser::LValContext::R_BRACKT() {
  return getTokens(BIFANGParser::R_BRACKT);
}

tree::TerminalNode* BIFANGParser::LValContext::R_BRACKT(size_t i) {
  return getToken(BIFANGParser::R_BRACKT, i);
}


size_t BIFANGParser::LValContext::getRuleIndex() const {
  return BIFANGParser::RuleLVal;
}

void BIFANGParser::LValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLVal(this);
}

void BIFANGParser::LValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLVal(this);
}


std::any BIFANGParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::LValContext* BIFANGParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 38, BIFANGParser::RuleLVal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(283);
    match(BIFANGParser::IDENT);
    setState(290);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(284);
        match(BIFANGParser::L_BRACKT);
        setState(285);
        exp(0);
        setState(286);
        match(BIFANGParser::R_BRACKT); 
      }
      setState(292);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

BIFANGParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::NumberContext::FLOAT_CONST() {
  return getToken(BIFANGParser::FLOAT_CONST, 0);
}

tree::TerminalNode* BIFANGParser::NumberContext::INTEGER_CONST() {
  return getToken(BIFANGParser::INTEGER_CONST, 0);
}


size_t BIFANGParser::NumberContext::getRuleIndex() const {
  return BIFANGParser::RuleNumber;
}

void BIFANGParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void BIFANGParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}


std::any BIFANGParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::NumberContext* BIFANGParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 40, BIFANGParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    _la = _input->LA(1);
    if (!(_la == BIFANGParser::FLOAT_CONST

    || _la == BIFANGParser::INTEGER_CONST)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOpContext ------------------------------------------------------------------

BIFANGParser::UnaryOpContext::UnaryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BIFANGParser::UnaryOpContext::PLUS() {
  return getToken(BIFANGParser::PLUS, 0);
}

tree::TerminalNode* BIFANGParser::UnaryOpContext::MINUS() {
  return getToken(BIFANGParser::MINUS, 0);
}

tree::TerminalNode* BIFANGParser::UnaryOpContext::NOT() {
  return getToken(BIFANGParser::NOT, 0);
}


size_t BIFANGParser::UnaryOpContext::getRuleIndex() const {
  return BIFANGParser::RuleUnaryOp;
}

void BIFANGParser::UnaryOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOp(this);
}

void BIFANGParser::UnaryOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOp(this);
}


std::any BIFANGParser::UnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitUnaryOp(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::UnaryOpContext* BIFANGParser::unaryOp() {
  UnaryOpContext *_localctx = _tracker.createInstance<UnaryOpContext>(_ctx, getState());
  enterRule(_localctx, 42, BIFANGParser::RuleUnaryOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8394752) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

BIFANGParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BIFANGParser::ParamContext *> BIFANGParser::FuncRParamsContext::param() {
  return getRuleContexts<BIFANGParser::ParamContext>();
}

BIFANGParser::ParamContext* BIFANGParser::FuncRParamsContext::param(size_t i) {
  return getRuleContext<BIFANGParser::ParamContext>(i);
}

std::vector<tree::TerminalNode *> BIFANGParser::FuncRParamsContext::COMMA() {
  return getTokens(BIFANGParser::COMMA);
}

tree::TerminalNode* BIFANGParser::FuncRParamsContext::COMMA(size_t i) {
  return getToken(BIFANGParser::COMMA, i);
}


size_t BIFANGParser::FuncRParamsContext::getRuleIndex() const {
  return BIFANGParser::RuleFuncRParams;
}

void BIFANGParser::FuncRParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncRParams(this);
}

void BIFANGParser::FuncRParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncRParams(this);
}


std::any BIFANGParser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::FuncRParamsContext* BIFANGParser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 44, BIFANGParser::RuleFuncRParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    param();
    setState(302);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BIFANGParser::COMMA) {
      setState(298);
      match(BIFANGParser::COMMA);
      setState(299);
      param();
      setState(304);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

BIFANGParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::ExpContext* BIFANGParser::ParamContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}


size_t BIFANGParser::ParamContext::getRuleIndex() const {
  return BIFANGParser::RuleParam;
}

void BIFANGParser::ParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam(this);
}

void BIFANGParser::ParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam(this);
}


std::any BIFANGParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::ParamContext* BIFANGParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 46, BIFANGParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    exp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstExpContext ------------------------------------------------------------------

BIFANGParser::ConstExpContext::ConstExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BIFANGParser::ExpContext* BIFANGParser::ConstExpContext::exp() {
  return getRuleContext<BIFANGParser::ExpContext>(0);
}


size_t BIFANGParser::ConstExpContext::getRuleIndex() const {
  return BIFANGParser::RuleConstExp;
}

void BIFANGParser::ConstExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstExp(this);
}

void BIFANGParser::ConstExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BIFANGParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstExp(this);
}


std::any BIFANGParser::ConstExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BIFANGParserVisitor*>(visitor))
    return parserVisitor->visitConstExp(this);
  else
    return visitor->visitChildren(this);
}

BIFANGParser::ConstExpContext* BIFANGParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 48, BIFANGParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(307);
    exp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool BIFANGParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 17: return expSempred(antlrcpp::downCast<ExpContext *>(context), predicateIndex);
    case 18: return condSempred(antlrcpp::downCast<CondContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool BIFANGParser::expSempred(ExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool BIFANGParser::condSempred(CondContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 4);
    case 3: return precpred(_ctx, 3);
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void BIFANGParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  bifangparserParserInitialize();
#else
  ::antlr4::internal::call_once(bifangparserParserOnceFlag, bifangparserParserInitialize);
#endif
}
