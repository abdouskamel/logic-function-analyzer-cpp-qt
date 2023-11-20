#include "tokens_exception.h"

TokensException::TokensException(QString const& what, Tokens const& tokens, int pos) throw()
    : m_what(what), m_tokens(tokens), m_pos(pos)
{

}

TokensException::~TokensException() throw()
{

}

const char*
TokensException::what() const throw()
{
    return m_what.toStdString().c_str();
}

Tokens
TokensException::getTokens(void) const
{
    return m_tokens;
}

int
TokensException::getPosition(void) const
{
    return m_pos;
}
