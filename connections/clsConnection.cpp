#include "connections/clsConnection.h"
#include "connections/clsLan.h"
connectionFactory::connectionFactory()
{
}

/*通过工厂模式来获取连接的接口实例。
 *
 *V1.0
 *!*/

clsConnection *connectionFactory::getConnection(QString strConnect)
{

    if(strConnect.toUpper()=="LAN")
    {
        return new clsLan;
    }
    else
    {
        return (clsConnection *)0;
    }

}
