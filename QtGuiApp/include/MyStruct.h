#include <QMetaType>
#include <QString>

struct MyStruct
{
    int id;
    QString name;
};

Q_DECLARE_METATYPE(MyStruct) // 声明为元类型

// 在程序初始化阶段注册
void registerMyStructMetaType()
{
    qRegisterMetaType<MyStruct>("MyStruct");
}
