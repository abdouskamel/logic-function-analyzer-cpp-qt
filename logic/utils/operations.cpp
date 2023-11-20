#include "operations.h"

QString mno(QString const& a)
{
    if(a == "1")
        return "0";

    else
        return "1";
}

QString mxor(QString const& a, QString const& b)
{
    if(a == b)
        return "0";

    else
        return "1";
}

QString mand(QString const& a, QString const& b)
{
    if(a == "1" && b == "1")
        return "1";

    else
        return "0";
}

QString mor(QString const& a, QString const& b)
{
    if(a == "1" || b == "1")
        return "1";

    else
        return "0";
}
