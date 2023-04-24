#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    path_label = new QLabel("Audio File:", this);
    path_input = new QLineEdit(this);
    browse_button = new QPushButton("Browse", this);
    artist_label = new QLabel("Artist:", this);
    artist_input = new QLineEdit(this);
    title_label = new QLabel("Title:", this);
    title_input = new QLineEdit(this);
    album_label = new QLabel("Album:", this);
    album_input = new QLineEdit(this);
    genre_label = new QLabel("Genre:", this);
    genre_input = new QLineEdit(this);
    current_metadata_label = new QLabel("Current Metadata:", this);
    current_metadata = new QTextEdit(this);
    current_metadata->setReadOnly(true);
    save_button = new QPushButton("Save Changes", this);

    layout->addWidget(path_label);
    layout->addWidget(path_input);
    layout->addWidget(browse_button);
    layout->addWidget(artist_label);
    layout->addWidget(artist_input);
    layout->addWidget(title_label);
    layout->addWidget(title_input);
    layout->addWidget(album_label);
    layout->addWidget(album_input);
    layout->addWidget(genre_label);
    layout->addWidget(genre_input);
    layout->addWidget(current_metadata_label);
    layout->addWidget(current_metadata);
    layout->addWidget(save_button);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(browse_button, &QPushButton::clicked, this, &MainWindow::browseFile);
    connect(save_button, &QPushButton::clicked, this, &MainWindow::saveChanges);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browseFile()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Open audio file", "", "Audio Files (*.mp3 *.flac *.m4a *.ogg *.opus *.wav);;All Files (*)");
    if (!file_path.isEmpty())
    {
        path_input->setText(file_path);
        loadFile(file_path);
    }
}

void MainWindow::loadFile(const QString &file_path)
{
    audio_file = TagLib::FileRef(file_path.toStdString().c_str());
    if (!audio_file.isNull())
    {
        TagLib::Tag *tag = audio_file.tag();
        if (tag)
        {
            artist_input->setText(QString::fromStdString(tag->artist().toCString(true)));
            title_input->setText(QString::fromStdString(tag->title().toCString(true)));
            album_input->setText(QString::fromStdString(tag->album().toCString(true)));
            genre_input->setText(QString::fromStdString(tag->genre().toCString(true)));
        }
    }
    displayCurrentMetadata();
}

void MainWindow::displayCurrentMetadata()
{
    QString current_metadata = QString("Artist: %1\nTitle: %2\nAlbum: %3\nGenre: %4")
                                    .arg(artist_input->text())
                                    .arg(title_input->text())
                                    .arg(album_input->text())
                                    .arg(genre_input->text());
    current_metadata->setPlainText(current_metadata);
}

void MainWindow::saveChanges()
{
    if (!audio_file.isNull())
    {
        TagLib::Tag *tag = audio_file.tag();
        if (tag)
        {
            tag->setArtist(artist_input->text().toStdString());
            tag->setTitle(title_input->text().toStdString());
            tag->setAlbum(album_input->text().toStdString());
            tag->setGenre(genre_input->text().toStdString());
            audio_file.save();
        }
    }
    displayCurrentMetadata();
}
