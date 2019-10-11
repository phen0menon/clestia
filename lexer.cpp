#include <string>

union TokenValue {
  int intRepr;
  short shortRepr;
  char* pCharRepr;
  void* pVoidRepr;
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
  
  char currToken() {
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
    char tkn = this->currToken();
    if (isdigit(tkn)) {
      int startPos = _position;
      while (isdigit(tkn)) {
        this->next();
      }
      int finishPos = _position - startPos;
      std::string data = this->_data.substr(startPos, finishPos);
      TokenValue value;
      value.intRepr = std::stoi(data);
      return SyntaxToken(Whitespace, startPos, data, value);
    }

    if (isspace(tkn)) {
      int startPos = _position;
      while (isspace(tkn) ) {
        this->next();
      }
      int finishPos = _position - startPos;
      std::string data = this->_data.substr(startPos, finishPos);
      int tokenValue = std::stoi(data);
      TokenValue value;
      value.intRepr = std::stoi(data);
      return SyntaxToken(Whitespace, startPos, data, value);
    }
  }
};