#ifndef TOKENS_EXCEPTION_H
#define TOKENS_EXCEPTION_H

#include <exception>
#include <QString>
#include "my_const.h"

class TokensException : public std::exception
{
    public:
        TokensException(QString const& what, Tokens const& tokens, int pos) throw();
        virtual ~TokensException() throw();

        virtual const char* what() const throw();
        Tokens getTokens(void) const;
        int getPosition(void) const;

    protected:
        QString m_what;
        Tokens m_tokens;
        int m_pos;
};

#endif // TOKENS_EXCEPTION_H

