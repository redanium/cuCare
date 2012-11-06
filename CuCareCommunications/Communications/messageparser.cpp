#include "messageparser.h"
#include "commsinclude.h"

MessageParser::MessageParser()
{
}

ModelObject MessageParser::qVariantMapToModelObject(QVariantMap qvm)
{
    ModelObject mod;
    QJson::QObjectHelper::qvariant2qobject(qvm, &mod);
    return mod;
}


QVariantMap MessageParser::qByteArrayToqvMap(QByteArray qba)
{
    QJson::Parser parser;
    bool ok = true;
    QVariantMap vReturn = parser.parse(qba.right(qba.size() - JSON_LEADING_STRIP), &ok).toMap();
    if(ok){return vReturn;}
    else{throw("failed to parse json");}
}
