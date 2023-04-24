#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <taglib/tag.h>
#include <taglib/fileref.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void browseFile();
    void loadFile(const QString &file_path);
    void displayCurrentMetadata();
    void saveChanges();

private:
    Ui::MainWindow *ui;
    QLabel *path_label;
    QLineEdit *path_input;
    QPushButton *browse_button;
    QLabel *artist_label;
    QLineEdit *artist_input;
    QLabel *title_label;
    QLineEdit *title_input;
    QLabel *album_label;
    QLineEdit *album_input;
    QLabel *genre_label;
    QLineEdit *genre_input;
    QLabel *current_metadata_label;
    QTextEdit *current_metadata;
    QPushButton *save_button;

    TagLib::FileRef audio_file;
};
#endif // MAINWINDOW_H
