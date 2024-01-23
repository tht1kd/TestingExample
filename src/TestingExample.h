#include <QQmlExtensionPlugin>

class TestingExamplePlugin: public QQmlExtensionPlugin
{
    Q_OBJECT

public:
    void registerTypes(const char* uri) override {
        Q_ASSERT(QLatin1String("TestingExample") == QLatin1String(uri));
        qmlRegisterType<CustomComponent>(uri, 1, 0 "CustomComponent");
    }
};
