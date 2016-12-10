#include <QObject>
#include <QString>
#include <QByteArray>
#include <QSharedPointer>

using ImageBuffer = QSharedPointer<QByteArray>;

class MainWindow : public QObject
{
	Q_OBJECT

public:
	explicit MainWindow(QObject *parent = nullptr);

signals:
	void imageDownloaded(QByteArray *buffer);

public slots:
	void convert(QString url, QString format);

private:
	ImageBuffer downloadImage(const QString &url);

	QString askForFilename(const QString &format);
};
