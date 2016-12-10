#include <QDebug>
#include <QFileDialog>

#include <Magick++.h>

#include <curl/curl.h>

#include "mainwindow.h"

static size_t onCurlWrite(const char *data, size_t size, size_t nmemb, QByteArray *buffer)
{	
	size_t actualSize = size * nmemb;
	buffer->append(data, actualSize);
	return actualSize;
}

MainWindow::MainWindow(QObject *parent /* = nullptr */)
	: QObject(parent)
{
}

void MainWindow::convert(QString url, QString format)
{
	auto imagebuffer = downloadImage(url);
	emit imageDownloaded(imagebuffer.data());

	QString filename = askForFilename(format);

	Magick::Blob blob(
		static_cast<const void *>(imagebuffer->constData()),
		imagebuffer->size()
	);

	Magick::Image image(blob);
	image.magick(format.toStdString().c_str());
	image.write(filename.toStdString().c_str());
}

ImageBuffer MainWindow::downloadImage(const QString &url)
{
	curl_global_init(CURL_GLOBAL_ALL);

	CURL *curl = curl_easy_init();
	if(curl == nullptr) {
		qCritical() << "Failed to initialize CURL";
		return ImageBuffer();
	}

	ImageBuffer buffer = QSharedPointer<QByteArray>::create();

	curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer.data());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onCurlWrite);

	CURLcode result = curl_easy_perform(curl);

	if(result != CURLE_OK) {
		qCritical() << "Failed to make request, error " << result;
		return ImageBuffer();
	}

	return buffer;	
}

QString MainWindow::askForFilename(const QString &format)
{
	QString filter = QString("%1 file (*.%2)").arg(
		format,
		format.toLower()
	);

	return QFileDialog::getSaveFileName(
		nullptr,
		"Save image",
		"/",
		filter
	);
}
