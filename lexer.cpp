#include <string>

union TokenValue {
  int intRepr;
  short shortRepr;
  char* pCharRepr;
  void* pVoidRepr;
  TokenValue(int repr) : intRepr(repr) {}
  TokenValue(short repr) : shortRepr(repr) {}
  TokenValue(char* repr) : pCharRepr(repr) {}
  TokenValue(void* repr) : pVoidRepr(repr) {}
};

enum SyntaxKind {
  Number,
  Whitespace
};

struct SyntaxToken {
  std::string _data; 
  SyntaxKind _kind;
  int _position;
  TokenValue _value;

  SyntaxToken(SyntaxKind kind, int position, std::string data, TokenValue value) :
    _kind(kind), _position(position), _data(data), _value(value) {}
};

class Lexer {
private:
  std::string _data;
  int _position;
  
  char currentChar() {
    if (_position > _data.length) {
      return '\0';
    }
    return _data[_position];
  }

public:
  Lexer(std::string data) : _data(data) {}

  void next() {
    this->_position++;
  }

  SyntaxToken nextToken() {
    char tkn = this->currentChar();
    if (isdigit(tkn)) {
      int startPos = _position;
      while (isdigit(tkn)) {
        this->next();
      }
      int finishPos = _position - startPos;
      std::string data = this->_data.substr(startPos, finishPos);
      return SyntaxToken(Number, startPos, data, TokenValue(std::stoi(data)));
    }

    if (isspace(tkn)) {
      int startPos = _position;
      while (isspace(tkn) ) {
        this->next();
      }
      int finishPos = _position - startPos;
      std::string data = this->_data.substr(startPos, finishPos);
      return SyntaxToken(Whitespace, startPos, data, TokenValue(std::stoi(data)));
    }
  }
};