// photoshop.h

#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include <QMainWindow>
// #include <iostream>
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
    void selectImage(); // Declaration of the selectImage function

    void on_save_image_clicked();

    void on_gray_scale_clicked();

    void on_black_an_white_clicked();

    void on_invert_image_clicked();

    void on_detected_image_clicked();

    void on_wano_day_clicked();

    void on_oil_painted_clicked();

    void on_clear_image_clicked();

    void on_channed_swaped_clicked();

    void on_skewButton_clicked();

    void on_blurButton_clicked();

    void on_pixel_image_clicked();

    void on_InferaRed_clicked();

    void on_wanoTv_clicked();

    void on_wanoNight_clicked();

    void on_flip_hori_clicked();

    void on_flip_ver_clicked();

    void on_resize_image_clicked();

    void on_rotate_clicked();

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

    void on_frame_image_clicked();

    void on_cropImage_clicked();

    void on_megre_Image_clicked();

    void mergeselect();

    void closeEvent(QCloseEvent *event);

    void undoShortcut();

    void redoOperation();

    void save_change();

    void on_editBrightness_clicked();

    void on_brightness_sliderMoved();

    void save_as();

    void save_same();

    void restore();
private:
    Ui::MainWindow *ui;

};

#endif // PHOTOSHOP_H
