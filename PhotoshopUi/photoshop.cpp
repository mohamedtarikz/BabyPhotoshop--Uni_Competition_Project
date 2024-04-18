#include <QtGlobal>
#include "photoshop.h"
#include "ui_photoshop.h"
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QInputDialog>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QRubberBand>
#include <QMouseEvent>
#include <cmath>
#include <library/image_class.h>
#include <QShortcut>
#include <QKeySequence>
#include <stack>
#include <QCloseEvent>
std::stack<Image> imageStack;
std::stack<Image> redoStack;


Image img_in;
Image img_filter;
Image img_out;
Image megred;
QString LoadedImagePath;
QPoint origin;
QRubberBand *rubberBand = NULL;
QSize fxdSz;
QSize imgSz;

bool SV = true;
bool crp_prsd = false;
bool fltrd = true;
bool insrt = false;
bool brtns =false;
bool mrg;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->brightness->setVisible(brtns);

    // Connect the QPushButton's clicked signal to the slot function
    connect(ui->insert_image, &QPushButton::clicked, this, &MainWindow::selectImage);

    // Connect the customContextMenuRequested signal of the save_image button to on_save_image_customContextMenuRequested slot
    connect(ui->save_image, &QPushButton::clicked, this, &MainWindow::on_save_image_clicked);
    QShortcut *shortcutUndo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);

    // Connect the activated signal of the shortcut to the undoOperation slot
    connect(shortcutUndo, &QShortcut::activated, this, &MainWindow::undoShortcut);

    QShortcut *shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    connect(shortcutRedo, &QShortcut::activated, this, &MainWindow::redoOperation);

    QShortcut *saveCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);
    connect(saveCut, &QShortcut::activated, this, &MainWindow::save_same);


    QShortcut *saveAsCut = new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S), this);
    connect(saveAsCut, &QShortcut::activated, this, &MainWindow::save_as);

    QShortcut *insertCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this);
    connect(insertCut, &QShortcut::activated, this, &MainWindow::selectImage);

    showMaximized();


}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::save_change(){
    SV = false;
    QImage updatedImage(img_filter.width, img_filter.height, QImage::Format_RGB888);

    // Iterate through each pixel to set the corresponding pixel in the QImage
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Get the RGB values for the pixel
            int red = img_filter(i, j, 0);
            int green = img_filter(i, j, 1);
            int blue = img_filter(i, j, 2);

            // Set the pixel in the QImage
            updatedImage.setPixel(i, j, qRgb(red, green, blue));
        }
    }

    // Calculate the scaled size based on the label's size
    int h = ui->frame_2->height();
    int w = ui->frame_2->width();
    h-=25;
    double scale = (double)h/img_filter.height;
    fxdSz = QSize(qMin( scale*img_filter.width,(double)w-25),h);
    imgSz = updatedImage.size().scaled(fxdSz, Qt::KeepAspectRatio);
    QSize scaledSize = imgSz;

    // Convert the QImage to a QPixmap
    QPixmap pixmap = QPixmap::fromImage(updatedImage.scaled(scaledSize, Qt::KeepAspectRatio));

    // Update the label with the QPixmap and keep the label's size fixed
    ui->image_label->setPixmap(pixmap);
    ui->image_label->setFixedSize(pixmap.size());
}

void MainWindow::restore(){
    brtns = 0;
    ui->brightness->setVisible(0);
    QImage updatedImage(img_filter.width, img_filter.height, QImage::Format_RGB888);

    // Iterate through each pixel to set the corresponding pixel in the QImage
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Get the RGB values for the pixel
            int red = img_filter(i, j, 0);
            int green = img_filter(i, j, 1);
            int blue = img_filter(i, j, 2);

            // Set the pixel in the QImage
            updatedImage.setPixel(i, j, qRgb(red, green, blue));
        }
    }

    // Calculate the scaled size based on the label's size
    int h = ui->frame_2->height();
    int w = ui->frame_2->width();
    ui->frame_2->setFixedHeight(h+35);
    //ui->frame_2->setFixedWidth(w+35);
    h+=10;
    w-=25;
    double scale = (double)h/img_filter.height;
    fxdSz = QSize(qMin( scale*img_filter.width,(double)w),h);
    imgSz = updatedImage.size().scaled(fxdSz, Qt::KeepAspectRatio);
    QSize scaledSize = imgSz;

    // Convert the QImage to a QPixmap
    QPixmap pixmap = QPixmap::fromImage(updatedImage.scaled(scaledSize, Qt::KeepAspectRatio));

    // Update the label with the QPixmap and keep the label's size fixed
    ui->image_label->setPixmap(pixmap);
    ui->image_label->setFixedSize(pixmap.size());
}

void MainWindow::selectImage()
{
    // Open file dialog to select an image
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    // Check if a file is selected
    if (!fileName.isEmpty()) {
        try {
            // Load the image from file
            QImage image(fileName);

            // Check if the image is valid
            if (!image.isNull()) {
                // Set the filter image to the loaded image
                img_in.loadNewImage(fileName.toStdString());
                img_filter = img_in; // Initialize img_filter with img_in

                // Resize the image to match the dimensions of the edited image (img_filter)
                int h = ui->frame_2->height();
                int w = ui->frame_2->width();
                SV = false;
                h-=25;
                double scale = (double)h/img_in.height;
                fxdSz = QSize(qMin(scale*img_in.width,(double)w-25),h);
                imgSz = image.size().scaled(fxdSz, Qt::KeepAspectRatio);
                QSize scaledSize = imgSz;

                // Convert the QImage to a QPixmap
                QPixmap pixmap = QPixmap::fromImage(image.scaled(scaledSize, Qt::KeepAspectRatio));

                // Update the label with the QPixmap and keep the label's size fixed
                ui->image_label->setPixmap(pixmap);
                ui->image_label->setFixedSize(pixmap.size());
                LoadedImagePath = fileName;
                insrt = true;
            } else {
                // Display an error message if the image cannot be loaded
                QMessageBox::warning(this, tr("Error"), tr("Failed to load image!"));
            }
        } catch (const std::invalid_argument&){
            // Catch exception if image loading fails
            QMessageBox::warning(this, tr("Error"), tr("Failed to load image!"));
        }
    }
}
void MainWindow :: save_as(){
    if (LoadedImagePath.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("No image loaded!"));
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        // Save the image using the fileName
        try {
            img_filter.saveImage(fileName.toStdString());
            QMessageBox::information(this, tr("Image Saved"), tr("Image saved successfully!"));
            SV = true;
        } catch (const std::exception &e) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to save image: %1").arg(e.what()));
        }
    }

}

void MainWindow :: save_same(){
    if (LoadedImagePath.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("No image loaded!"));
        return;
    }

    // Save the modified image using the original file path
    try {
        img_filter.saveImage(LoadedImagePath.toStdString());
        QMessageBox::information(this, tr("Image Saved"), tr("Image saved successfully!"));
        SV = true;
    } catch (const std::exception &e) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to save image: %1").arg(e.what()));
    }

}

void MainWindow::on_save_image_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    // Create a menu with the save actions
    QMenu menu(this);
    QAction *actionSaveNew = menu.addAction("Save as New Image");
    QAction *actionSaveReplace = menu.addAction("Replace the Existing Image");

    // Connect the triggered signal of the "Save as New Image" action
    connect(actionSaveNew, &QAction::triggered, this, [this]() {
        // Save the image as a new file
        save_as();

    });

    // Connect the triggered signal of the "Replace the Existing Image" action
    connect(actionSaveReplace, &QAction::triggered, this, [this]() {
        // Ensure an image is loaded
        save_same();
    });

    // Show the menu at the position of the save button
    menu.exec(ui->save_image->mapToGlobal(QPoint(0, ui->save_image->height())));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(SV){
        event->accept();
    }
    else{
        QMessageBox::StandardButton resBtn = QMessageBox::question(this,"Confirmation",tr("You didn't save!\nAre you sure you want to Exit?"),QMessageBox::No | QMessageBox::Yes,QMessageBox::No);

        if (resBtn != QMessageBox::Yes) {
            event->ignore();
            if(brtns){
                restore();
            }
        } else {
            event->accept();
        }
    }
}

void greyscale() {

    // Iterate through each pixel in the image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            int av = 0; // Initialize average value
            // Calculate average pixel value across RGB channels
            for (int k = 0; k < 3; k++) {
                av += img_filter(i, j, k);
            }
            av /= 3; // Compute the average
            // Set each RGB channel to the average value to convert to grayscale
            for (int k = 0; k < 3; k++) {
                img_filter(i, j, k) = av;
            }
        }
    }
}


void MainWindow::on_gray_scale_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }
    greyscale();
    // After applying the grayscale transformation, create a QImage from the pixel data
    save_change();
}



void MainWindow::on_black_an_white_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    // prev_img_filter = img_filter;
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }
    greyscale();
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Set the color of the pixel to max white or black
            for (int k = 0; k < 3; k++) {
                if (img_filter(i, j, k) < 128) {
                    img_filter(i, j, k) = 0;
                } else {
                    img_filter(i, j, k) = 255;
                }
            }
        }
    }
    save_change();
}



void MainWindow::on_invert_image_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }
    // Iterate through each pixel in the image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Invert each RGB channel by subtracting from 255
            for (int k = 0; k < 3; k++) {
                img_filter(i, j, k) = 255 - img_filter(i, j, k);
            }
        }
    }

    // After inverting the image, create a QImage from the pixel data
    save_change();
}
void black_and_white() {
    // Convert the input image to grayscale
    greyscale();
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Set the color of the pixel to max white or black
            for (int k = 0; k < 3; k++) {
                if (img_filter(i, j, k) < 128) {
                    img_filter(i, j, k) = 0;
                } else {
                    img_filter(i, j, k) = 255;
                }
            }
        }
    }
}

// Function to crop an image
void detect_edge() {
    imageStack.push(img_filter);

    // Convert input image to black and white
    black_and_white();
    Image img_Detected_edges(img_filter.width, img_filter.height);
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                // Check if the current pixel is not on the image border
                if (i != 0 && i != img_filter.width - 1 && j != 0 && j != img_filter.height - 1) {
                    // Check if the current pixel is black and any of its neighboring pixels are white
                    if ((img_filter(i, j, k) == 0 && img_filter(i - 1, j, k) == 255) ||
                        (img_filter(i, j, k) == 0 && img_filter(i + 1, j, k) == 255) ||
                        (img_filter(i, j, k) == 0 && img_filter(i, j - 1, k) == 255) ||
                        (img_filter(i, j, k) == 0 && img_filter(i, j + 1, k) == 255)) {
                        // If any of the neighboring pixels are white, set the corresponding pixel in Detected_edges to black
                        img_Detected_edges(i, j, k) = 0;
                    } else {
                        // If none of the neighboring pixels are white, set the corresponding pixel in Detected_edges to white
                        img_Detected_edges(i, j, k) = 255;
                    }
                } else {
                    // If the pixel is on the image border, retain its original color in Detected_edges
                    img_Detected_edges(i, j, k) = img_filter(i, j, k);
                }
            }
        }
    }
    img_filter = img_Detected_edges;
}
void MainWindow::on_detected_image_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }
    // Process the image to detect edges
    detect_edge();

    // Create a QImage from the processed image data
    save_change();
}
void MainWindow::on_wano_day_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }


    // Create a new image with the same dimensions as the input image
    Image Wanno_Day_img(img_filter.width, img_filter.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            Wanno_Day_img(i, j, 0) = qMin((img_filter(i, j, 0) + 20), 255);
            Wanno_Day_img(i, j, 1) = qMin((img_filter(i, j, 1) + 20), 255);
            Wanno_Day_img(i, j, 2) = qMax((img_filter(i, j, 2) - 40), 0);
        }
    }
    img_filter = Wanno_Day_img;
    save_change();

}
void oil_painted() {
    imageStack.push(img_filter);

    // Create a copy of the input image to store the oil-painted effect
    Image img_oil_paint(img_filter);
    // Reduce the color precision of each pixel
    for (int i = 0; i < img_oil_paint.width; i++) {
        for (int j = 0; j < img_oil_paint.height; j++) {
            for (int k = 0; k < 3; k++) {
                // Divide the color value of each channel by 40 to reduce precision
                img_oil_paint(i, j, k) /= 40;
                // Multiply the result by 40 to bring it closer to its original value
                img_oil_paint(i, j, k) *= 40;
            }
        }
    }
    // Update the input image with the oil-painted result
    img_filter = img_oil_paint;
}



void MainWindow::on_oil_painted_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    oil_painted();
    save_change();
}


void MainWindow::on_clear_image_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    // Reset the filtered image to the original input image
    img_filter = img_in;
    crp_prsd = false;
    brtns = false;
    ui->brightness->setVisible(brtns);
    fltrd = true;
    // Convert the original image to a QImage
    save_change();
}
void channel_swap() {
    Image edited(img_filter.width,img_filter.height);
    // Loop through each column of the image
    for (int i = 0; i < img_filter.width; i++) {
        // Loop through each row of the image
        for (int j = 0; j < img_filter.height; ++j) {
            for (int k = 0; k<3 ; k++) {
                // Swap the red channel (index 0) with the blue channel (index 2)
                edited(i, j, 0) = img_filter(i, j, 2);
                // Swap the green channel (index 1) with the blue channel (index 2)
                edited(i, j, 1) = img_filter(i, j, 0);

                edited(i, j, 2) = img_filter(i, j, 1);

            }
        }
    }
    img_filter=edited;
}
void MainWindow::on_channed_swaped_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    channel_swap();
    save_change();
}
void MainWindow::on_skewButton_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    bool ok;
    double angle;
    while (true) {
        QString angleText = QInputDialog::getText(this, tr("Enter Skew Angle"), tr("Angle (degrees):"), QLineEdit::Normal,QString(), &ok);
        if (!ok) return; // User canceled, do nothing
        if (angleText.isEmpty()) {
            QMessageBox::warning(this, tr("Invalid Radius"), tr("Please enter a radius value."));
            continue;
        }

        angle = angleText.toDouble();
        if (((int)angle % 90) == 0 || angle > 5000) {
            QMessageBox::warning(this, tr("Invalid Angle"), tr("Please enter a proper angle between 0 and 5000, excluding multiples of 90."));
            continue;
        }

        // Valid radius entered, break out of the loop
        break;
    }
    // Calculate the width expansion due to skewing
    int w = qCeil(img_filter.height * qTan(angle * M_PI / 180.0));

    // Create a new image for the skewed result
    Image img_skewed(img_filter.width + w, img_filter.height);

    // Fill the new image with white color
    // This part needs modification in the Image class to support filling with a specific color
    // img_skewed.fill(Qt::white);

    // Fill the new image with white color
    for (int i = 0; i < img_skewed.width; i++) {
        for (int j = 0; j < img_skewed.height; j++) {
            for (int k = 0; k < 3; k++) {
                img_skewed(i, j, k) = 255;
            }
        }
    }

    // Skew the original image and copy it to the new image
    int c = 0;
    for (int i = w; i < img_skewed.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                // Copy the pixel value from the original image to the skewed image
                img_skewed.setPixel(i - c, j, k, img_filter.getPixel(i - w, j, k));
            }
            // Calculate the horizontal offset (c) for each row in the skewed image based on the skew angle and current row index (j)
            c = qCeil(j * qTan(angle * M_PI / 180.0));
        }
        c = 0;
    }

    // Update the input image with the skewed result
    img_filter =img_skewed;
    save_change();

}
void blurImage(int radius)
{

    int  sr, er, sc, ec;
    long long int sum, area;

    // Create a new image for the blurred result with the same dimensions as the input image
    Image blur_img(img_filter.width, img_filter.height);

    // Store the width and height of the input image
    int w = img_filter.width;
    int h = img_filter.height;

    // Initialize cumulative arrays for each color channel using dynamic memory allocation
    long long int*** cmlt = new long long int** [w + 1];
    long long int*** row = new long long int** [w + 1];

    for (int i = 0; i <= w; ++i) {
        cmlt[i] = new long long int* [h + 1];
        row[i] = new long long int* [h + 1];
        for (int j = 0; j <= h; ++j) {
            cmlt[i][j] = new long long int[3];
            row[i][j] = new long long int[3];
            memset(cmlt[i][j], 0, sizeof(long long int) * 3); // Initialize cumulative arrays with zeros
            memset(row[i][j], 0, sizeof(long long int) * 3);   // Initialize row arrays with zeros
        }
    }

    // Copy pixel values from input image to cumulative and row arrays
    for (int i = 1; i <= w; ++i) {
        for (int j = 1; j <= h; ++j) {
            for (int k = 0; k < 3; ++k) {
                cmlt[i][j][k] = row[i][j][k] = img_filter(i - 1, j - 1, k); // Copy pixel values
            }
        }
    }

    // Calculate cumulative sum for each row
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            for (int k = 0; k < 3; k++) {
                row[i][j][k] += row[i - 1][j][k]; // Add previous pixel value in row
            }
        }
    }

    // Calculate cumulative sum for each column
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            for (int k = 0; k < 3; k++) {
                if (!i)
                    cmlt[j][i][k] = row[j][i][k]; // First row cumulative sum is same as row value
                else if (!j) {
                    cmlt[j][i][k] += cmlt[j][i - 1][k]; // Add previous column value
                } else {
                    cmlt[j][i][k] = cmlt[j][i - 1][k] + row[j][i][k]; // Add previous row and column value
                }
            }
        }
    }

    // Apply blur to each pixel
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            for (int k = 0; k < 3; k++) {
                // Define region of pixels to be blurred
                sc = qMax(i - radius, 1); ec = qMin(i + radius, w);
                sr = qMax(j - radius, 1); er = qMin(j + radius, h);
                area = ((er - sr) * (ec - sc));

                // Calculate sum of pixel values within the region
                sum = cmlt[ec][er][k] - cmlt[ec][sr - 1][k] - cmlt[sc - 1][er][k] + cmlt[sc - 1][sr - 1][k];

                // Calculate average pixel value within the region
                sum /= area;

                // Set blurred pixel value in the output image
                blur_img(i - 1, j - 1, k) = (sum <= 255 ? sum : 255); // Clamp to maximum pixel value (255)
            }
        }
    }

    // Update the input image with the blurred image
    img_filter = blur_img;

    // Deallocate memory
    for (int i = 0; i <= w; ++i) {
        for (int j = 0; j <= h; ++j) {
            delete[] cmlt[i][j];
            delete[] row[i][j];
        }
        delete[] cmlt[i];
        delete[] row[i];
    }
    delete[] cmlt;
    delete[] row;

    // Update the label with the blurred image

}
int RM;
void MainWindow::on_blurButton_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    // Get the blur radius value from the horizontal slider
    while (true) {
        // Create a dialog to host the spin boxes and sliders
        QDialog dialog(this);
        dialog.setWindowTitle(tr("Enter Variables"));

        // Layout for the dialog
        QVBoxLayout layout(&dialog);

        // Create a widget to hold all the elements
        QWidget widget;
        QHBoxLayout widgetLayout(&widget);

        // Create the label for the slider
        QLabel widthLabel;

        // Create the slider for the blur value
        QSlider *sliderblur = new QSlider(Qt::Horizontal);
        sliderblur->setRange(3, 100); // Set the range of the slider
        sliderblur->setValue(0); // Set initial value
        sliderblur->setMinimumWidth(300);

        // Create the spin box for the blur value
        QSpinBox *spinBoxBlur = new QSpinBox();
        spinBoxBlur->setRange(3, 100); // Set the range of the spin box
        spinBoxBlur->setValue(0); // Set initial value
        spinBoxBlur->setMinimumWidth(50);

        // Add widgets to the layout
        widgetLayout.addWidget(&widthLabel);
        widgetLayout.addWidget(sliderblur);
        widgetLayout.addWidget(spinBoxBlur);

        // Add the widget to the layout
        layout.addWidget(&widget);

        // Add OK and Cancel buttons
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        layout.addWidget(&buttonBox);

        // Connect buttons to slots
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        // Connect slider value change to update the spin box value
        connect(sliderblur, &QSlider::valueChanged, spinBoxBlur, &QSpinBox::setValue);

        // Connect spin box value change to update the slider value


        // Connect slider value change to update the label text
        connect(spinBoxBlur, QOverload<int>::of(&QSpinBox::valueChanged), sliderblur, &QSlider::setValue);
        // });


        // Execute the dialog
        if (dialog.exec() == QDialog::Accepted) {
            // Retrieve the values from the spin box and sliders
            RM = sliderblur->value();


            // Use the values as needed
            break; // Exit the loop since we have valid input
        } else {
            // User canceled, exit the function
            return;
        }
    }


    // Perform the blur operation
    blurImage(RM);
    save_change();
}

void pixelate(int r) {
    // Prompt user for pixelation radius


    // Create a new image to store the pixelated result
    Image pixels(img_filter.width, img_filter.height);
    // Iterate through the image pixels with step size of r
    for (int i = 0; i < img_filter.width; i += r) {
        for (int j = 0; j < img_filter.height; j += r) {
            for (int k = 0; k < 3; k++) {
                unsigned char x = img_filter(i, j, k);
                // Find the maximum color value within the pixel block
                for (int l = 0; l < r; ++l) {
                    for (int m = 0; m < r; ++m) {
                        x = qMax((int)x, (int)img_filter(qMin(i + l, img_filter.width - 1), qMin(j + m, img_filter.height - 1), k));
                    }
                }
                // Set the pixel block to the maximum color value
                for (int l = 0; l < r; ++l) {
                    for (int m = 0; m < r; ++m) {
                        pixels(qMin(i + l, img_filter.width - 1), qMin(j + m, img_filter.height - 1), k) = x;
                    }
                }
            }
        }
    }
    // Update the input image with the pixelated result
    img_filter = pixels;
}
int RK;
void MainWindow::on_pixel_image_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    // Get the pixelation radius value from the horizontal slider
    // int R = ui->pixelslider->value();
    while (true) {
        // Create a dialog to host the spin box and slider
        QDialog dialog(this);
        dialog.setWindowTitle(tr("Enter Variables"));

        // Layout for the dialog
        QVBoxLayout layout(&dialog);

        // Create a widget to hold all the elements
        QWidget widget;
        QHBoxLayout widgetLayout(&widget);

        // Create the label for the slider
        QLabel widthpixel("(0 - 10)");

        // Create the slider for the pixel value
        QSlider *sliderpixel = new QSlider(Qt::Horizontal);
        sliderpixel->setRange(0, 10); // Set the range of the slider
        sliderpixel->setValue(0); // Set initial value
        sliderpixel->setMinimumWidth(200);

        // Create the spin box for the pixel value
        QSpinBox *spinBoxPixel = new QSpinBox();
        spinBoxPixel->setRange(0, 10); // Set the range of the spin box
        spinBoxPixel->setValue(0); // Set initial value
        spinBoxPixel->setMinimumWidth(50);

        // Add widgets to the layout
        widgetLayout.addWidget(&widthpixel);
        widgetLayout.addWidget(sliderpixel);
        widgetLayout.addWidget(spinBoxPixel);

        // Add the widget to the layout
        layout.addWidget(&widget);

        // Add OK and Cancel buttons
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        layout.addWidget(&buttonBox);

        // Connect buttons to slots
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        // Connect slider value change to update the spin box value
        connect(sliderpixel, &QSlider::valueChanged, spinBoxPixel, &QSpinBox::setValue);

        // Connect spin box value change to update the slider value
        connect(spinBoxPixel, QOverload<int>::of(&QSpinBox::valueChanged), sliderpixel, &QSlider::setValue);

        // Execute the dialog
        if (dialog.exec() == QDialog::Accepted) {
            // Retrieve the value from the slider or spin box
            RK = sliderpixel->value();

            // Use the value as needed
            break; // Exit the loop since we have valid input
        } else {
            // User canceled, exit the function
            return;
        }
    }

    // Check if the pixelation radius is valid
    if (RK > 0) {
        // Perform the pixelation operation
        pixelate(RK);

        // Update the slider range
        // on_brightness_rangeChanged(ui->brightness->minimum(), ui->brightness->maximum());

       save_change();
    }
}
void MainWindow::on_InferaRed_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                // If the current channel is the red channel (k = 0)
                if (k == 0) {
                    // Set the red channel to the maximum value of 255
                    img_filter(i, j, k) = 255;
                } else {
                    // Otherwise, invert the current channel (subtract the value of the current channel from 255)
                    img_filter(i, j, k) = 255 - img_filter(i, j, k);
                }
            }
        }
    }
    save_change();
}



void MainWindow::on_wanoTv_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    srand(unsigned(time(0)));
    // Create a new image with the same dimensions as the input image
    Image Wanno_TV_img(img_filter.width, img_filter.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            for (int k = 0; k < 3; k++) {
                int randomvalue = rand() % 21;
                if (img_filter(i, j, k) > 20) { // If pixel has vale more than  225 set it to its original value
                    Wanno_TV_img(i, j, k) = qMin(int((img_filter(i, j, k) - randomvalue) * 1.07), 255); // subtract a random value  between 1 and 20 to make noise
                } else {
                    Wanno_TV_img(i, j, k) = img_filter(i, j, k) + 1;
                }
            }
        }
    }
    img_filter = Wanno_TV_img;
    save_change();
}


void MainWindow::on_wanoNight_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    // Create a new image with the same dimensions as the input image
    Image Wanno_Night_img(img_filter.width, img_filter.height);
    // Loop through each pixel in the input image
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            Wanno_Night_img(i, j, 0) = qMin((img_filter(i, j, 0) + 20), 255);
            Wanno_Night_img(i, j, 1) = qMax((img_filter(i, j, 1) - 40), 0);
            Wanno_Night_img(i, j, 2) = qMin((img_filter(i, j, 2) + 20), 255);
        }
    }
    img_filter = Wanno_Night_img;
    save_change();
}


void MainWindow::on_flip_hori_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    // Create a new image to store the horizontally flipped image
    Image img_flipped(img_filter.width, img_filter.height);
    // Iterate through each pixel in the image
    for (int i = img_filter.width - 1; i >= 0; i--) {
        for (int j = 0; j < img_filter.height; j++) {
            // Flip the image in the x-direction
            for (int k = 0; k < 3; k++) {
                img_flipped(img_filter.width - 1 - i, j, k) = img_filter(i, j, k);
            }
        }
    }
    img_filter = img_flipped;
   save_change();
}



void MainWindow::on_flip_ver_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    // Create a new image to store the vertically flipped image
    Image img_flipped(img_filter.width, img_filter.height);
    // Iterate through each pixel in the image
    for (int j = img_filter.height - 1; j >= 0; j--) {
        for (int i = 0; i < img_filter.width; i++) {
            // Flip the image in the y-direction
            for (int k = 0; k < 3; k++) {
                img_flipped(i, img_filter.height - 1 - j, k) = img_filter(i, j, k);
            }
        }
    }
    img_filter = img_flipped;
    save_change();
}

    // Calculate scaling factors for width
    // int scale1, scale2;
    // scale1 = qMax(width, newWidth) /qMin(newWidth, width);
    // scale2 = scale1 + 1;

    // // Calculate division of the new image width into two parts
    // int FirstPart = scale2 * qMin(newWidth, width) - qMax(width, newWidth);
    // int SecondPart = (qMax(width, newWidth) - scale1 * FirstPart) / scale2;
    // int StartofSecondpart = SecondPart * scale2;

    // // Create a new image with the desired width and original height
    // Image Resized(newWidth, height);

    // if (newWidth <= width) {
    //     // If the new width is less than or equal to the original width
    //     // Create two images representing the first and second parts of the resized image
    //     Image FirstImage(FirstPart, height);
    //     Image SecondImage(SecondPart, height);
    //     int idx, fixed, avrg;

    //     // For each row in the image
    //     for (int j = 0; j < height; j++) {
    //         idx = 0;
    //         fixed = StartofSecondpart;

    //         // Process the first part of the resized image
    //         for (int h = 0; h < FirstPart; h++) {
    //             for (int k = 0; k < 3; ++k) {
    //                 avrg = 0;
    //                 idx = fixed;

    //                 // Calculate average pixel value for each channel
    //                 for (int i = 0; i < scale1; i++) {
    //                     avrg += img_resize(idx, j, k);
    //                     idx++;
    //                     if (idx >= width) {
    //                         break;
    //                     }
    //                 }
    //                 avrg /= scale1;
    //                 // Assign the average pixel value to the corresponding position in the FirstImage
    //                 FirstImage(h, j, k) = qMin(avrg, 255);
    //             }
    //             fixed += scale1;
    //         }

    //         // Process the second part of the resized image
    //         idx = 0;
    //         fixed = 0;
    //         for (int h = 0; h < SecondPart; h++) {
    //             for (int k = 0; k < 3; ++k) {
    //                 avrg = 0;
    //                 idx = fixed;
    //                 for (int i = 0; i < scale2; i++) {
    //                     avrg += img_resize(idx, j, k);
    //                     idx++;
    //                     if (idx >= width) {
    //                         break;
    //                     }
    //                 }
    //                 avrg /= scale2;
    //                 // Assign the average pixel value to the corresponding position in the SecondImage
    //                 SecondImage(h, j, k) = qMin(avrg, 255);
    //             }
    //             fixed += scale2;
    //         }
    //     }

    //     // Merge the two parts into the final resized image
    //     for (int i = 0; i < Resized.height; i++) {
    //         for (int j = 0; j < Resized.width; ++j) {
    //             for (int k = 0; k < 3; ++k) {
    //                 Resized(j, i, k) = (j >= SecondPart ? FirstImage(j - SecondPart, i, k) : SecondImage(j, i, k));
    //             }
    //         }
    //     }
    // } else {
    //     // If the new width is greater than the original width
    //     // Process each row and scale the pixels accordingly
    //     int idx;
    //     for (int j = 0; j < height; j++) {
    //         idx = 0;
    //         for (int i = 0; i < width; i++) {
    //             if (i >= FirstPart) {
    //                 // Scale the pixels in the first part
    //                 for (int h = 0; h < scale2; h++) {
    //                     for (int k = 0; k < 3; ++k) {
    //                         Resized(idx, j, k) = img_resize(i, j, k);
    //                     }
    //                     idx++;
    //                 }
    //             } else {
    //                 // Scale the pixels in the second part
    //                 for (int h = 0; h < scale1; h++) {
    //                     for (int k = 0; k < 3; ++k) {
    //                         Resized(idx, j, k) = img_resize(i, j, k);
    //                     }
    //                     idx++;
    //                 }
    //             }
    //         }
    //     }
    // }

    // // Update the input image to the resized image
    // img_resize = Resized;
    // width = img_resize.width;
    // height = img_resize.height;

    // // Calculate scaling factors for height
    // scale1 = qMax(height, newHeight) / qMin(newHeight, height);
    // scale2 = scale1 + 1;

    // // Calculate division of the new image height into two parts
    // FirstPart = scale2 * qMin(newHeight, height) - qMax(height, newHeight);
    // SecondPart = (qMax(height, newHeight) - scale1 * FirstPart) / scale2;
    // StartofSecondpart = SecondPart * scale2;

    // // Create a new image with the resized width and desired height
    // Image Resizedall(width, newHeight);

    // if (newHeight <= height) {
    //     // If the new height is less than or equal to the original height
    //     // Create two images representing the first and second parts of the resized image
    //     Image FirstImage(width, FirstPart);
    //     Image SecondImage(width, SecondPart);
    //     int idx, fixed, avrg;

    //     // For each column in the image
    //     for (int j = 0; j < width; j++) {
    //         idx = 0;
    //         fixed = StartofSecondpart;

    //         // Process the first part of the resized image
    //         for (int h = 0; h < FirstPart; h++) {
    //             for (int k = 0; k < 3; ++k) {
    //                 avrg = 0;
    //                 idx = fixed;

    //                 // Calculate average pixel value for each channel
    //                 for (int i = 0; i < scale1; i++) {
    //                     avrg += img_resize(j, idx, k);
    //                     idx++;
    //                     if (idx >= height) {
    //                         break;
    //                     }
    //                 }
    //                 avrg /= scale1;
    //                 // Assign the average pixel value to the corresponding position in the FirstImage
    //                 FirstImage(j, h, k) = qMin(avrg, 255);
    //             }
    //             fixed += scale1;
    //         }

    //         // Process the second part of the resized image
    //         idx = 0;
    //         fixed = 0;
    //         for (int h = 0; h < SecondPart; h++) {
    //             for (int k = 0; k < 3; ++k) {
    //                 avrg = 0;
    //                 idx = fixed;
    //                 for (int i = 0; i < scale2; i++) {
    //                     avrg += img_resize(j, idx, k);
    //                     idx++;
    //                     if (idx >= height) {
    //                         break;
    //                     }
    //                 }
    //                 avrg /= scale2;
    //                 // Assign the average pixel value to the corresponding position in the SecondImage
    //                 SecondImage(j, h, k) = qMin(avrg, 255);
    //             }
    //             fixed += scale2;
    //         }
    //     }

    //     // Merge the two parts into the final resized image
    //     for (int j = 0; j < Resizedall.width; ++j) {
    //         for (int i = 0; i < Resizedall.height; i++) {
    //             for (int k = 0; k < 3; ++k) {
    //                 Resizedall(j, i, k) = (i >= SecondPart ? FirstImage(j, i - SecondPart, k) : SecondImage(j, i, k));
    //             }
    //         }
    //     }
    // } else {
    //     // If the new height is greater than the original height
    //     // Process each column and scale the pixels accordingly
    //     int idx;
    //     for (int j = 0; j < width; j++) {
    //         idx = 0;
    //         for (int i = 0; i < height; i++) {
    //             if (i >= FirstPart) {
    //                 // Scale the pixels in the first part
    //                 for (int h = 0; h < scale2; h++) {
    //                     for (int k = 0; k < 3; ++k) {
    //                         Resizedall(j, idx, k) = img_resize(j, i, k);
    //                     }
    //                     idx++;
    //                 }
    //             } else {
    //                 // Scale the pixels in the second part
    //                 for (int h = 0; h < scale1; h++) {
    //                     for (int k = 0; k < 3; ++k) {
    //                         Resizedall(j, idx, k) = img_resize(j, i, k);
    //                     }
    //                     idx++;
    //                 }
    //             }
    //         }
    //     }
    // }

    // // Return the resized image
    // return Resizedall;
Image resize1(Image img_resize, int newWidth, int newHeight) {
    int width = img_resize.width, height = img_resize.height;
    float scaleX = (float)newWidth / width;
    float scaleY = (float)newHeight / height;

    Image resizedImage(newWidth, newHeight);

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int orgX = x / scaleX;
            int orgY = y / scaleY;

            for (int channel = 0; channel < 3; ++channel) {
                resizedImage(x, y, channel) = img_resize(orgX, orgY, channel);
            }
        }
    }

    return resizedImage;
}


void MainWindow::on_resize_image_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    if(brtns){
        restore();
    }

    QMenu menuresize(this);
    QAction *resizedimention = menuresize.addAction("Resize by dimensions");
    QAction *resizescale = menuresize.addAction("Resize by scale");
    connect(resizedimention, &QAction::triggered, this, [this](){
        bool ok = false;
        int firstVariable;
        int secondVariable;

        while (true) {
            // Create a dialog to host the spin boxes
            QDialog dialog(this);
            dialog.setWindowTitle(tr("Enter Variables"));

            // Layout for the dialog
            QVBoxLayout layout(&dialog);

            // Create the first spin box
            QLabel label1("First Variable:");
            QSpinBox spinBox1;
            spinBox1.setMinimum(0); // Set minimum value
            spinBox1.setMaximum(999999999);

            layout.addWidget(&label1);
            layout.addWidget(&spinBox1);

            // Create the second spin box
            QLabel label2("Second Variable:");
            QSpinBox spinBox2;
            spinBox2.setMinimum(0); // Set minimum value
            spinBox2.setMaximum(999999999);
            layout.addWidget(&label2);
            layout.addWidget(&spinBox2);

            // Add OK and Cancel buttons
            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
            layout.addWidget(&buttonBox);

            // Connect buttons to slots
            connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
            connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

            // Execute the dialog
            if (dialog.exec() == QDialog::Accepted) {
                // Retrieve the values from the spin boxes
                firstVariable = spinBox1.value();
                secondVariable = spinBox2.value();

                // Check if both variables are valid
                if (firstVariable > 0 && secondVariable > 0) {
                    // Valid input, break out of the loop
                    ok = true;
                    break;
                } else {
                    // Invalid input, show a message and continue the loop
                    QMessageBox::warning(this, tr("Invalid Input"), tr("Please enter valid values for both variables."));
                }
            } else {
                // User canceled, break out of the loop
                break;
            }
        }
        if(ok){
            //Image img_resize = img_filter;
            img_filter = resize1(img_filter, firstVariable, secondVariable); // Resize the image

            // Now you have valid values for both variables, you can use them as needed
           save_change();

            imageStack.push(img_filter);
        }


    });
    connect(resizescale, &QAction::triggered, this, [this](){
        bool ok = false;
        double firstVariable;
        double secondVariable;

        while (true) {
            // Create a dialog to host the spin boxes
            QDialog dialog(this);
            dialog.setWindowTitle(tr("Enter Variables"));

            // Layout for the dialog
            QVBoxLayout layout(&dialog);

            // Create the first spin box
            QLabel label1("scale of width: (0 - 10)");
            QDoubleSpinBox spinBox1;
            spinBox1.setMinimum(0.0); // Set minimum value
            spinBox1.setMaximum(10);

            layout.addWidget(&label1);
            layout.addWidget(&spinBox1);

            // Create the second spin box
            QLabel label2("Scale height: (0 - 10)");
            QDoubleSpinBox spinBox2;
            spinBox2.setMinimum(0); // Set minimum value
            spinBox2.setMaximum(10);
            layout.addWidget(&label2);
            layout.addWidget(&spinBox2);


            // Add OK and Cancel buttons
            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
            layout.addWidget(&buttonBox);

            // Connect buttons to slots
            connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
            connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

            // Execute the dialog
            if (dialog.exec() == QDialog::Accepted) {
                // Retrieve the values from the spin boxes
                firstVariable = spinBox1.value();
                secondVariable = spinBox2.value();
                if(firstVariable==10||secondVariable==10){
                    QMessageBox::warning(this,tr("note"),tr("this will take sometime"));
                }

                // Check if both variables are valid
                if (firstVariable > 0 && secondVariable > 0) {
                    // Valid input, break out of the loop
                    ok = true;
                    break;
                } else {
                    // Invalid input, show a message and continue the loop
                    QMessageBox::warning(this, tr("Invalid Input"), tr("Please enter valid values for both variables."));
                }
            } else {
                // User canceled, break out of the loop
                break;
            }
        }
        if(ok){
            Image img_resize = img_filter;
            double newWidth = (double)(img_resize.width * firstVariable);
            double newHeight = (double)(img_resize.height * secondVariable);
            img_filter = resize1(img_filter, newWidth, newHeight); // Resize the image

            // Now you have valid values for both variables, you can use them as needed
           save_change();

            imageStack.push(img_filter);
        }

    });
    menuresize.exec(ui->resize_image->mapToGlobal(QPoint(0, ui->resize_image->height())));

}

Image crop_image(int x, int y, int w, int h) {
    // Initialize variables for iterating through cropped image
    int M = 0, N = 0;
    // Create a new image to store the cropped region
    Image img_cropped(w, h);
    // Iterate over the specified region of the input image and copy pixels to cropped image
    for (int i = x; i < w + x; i++) {
        for (int j = y; j < h + y; j++) {
            for (int k = 0; k < 3; k++) {
                // Copy pixel values from input image to cropped image
                img_cropped(M, N, k) = img_filter(i, j, k);
            }
            N++;
        }
        M++;
        N = 0;
    }
    return img_cropped;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    QPoint globalTopLeft = ui->image_label->mapToGlobal(ui->image_label->rect().topLeft());
    QPoint globalBottomRight = ui->image_label->mapToGlobal(ui->image_label->rect().bottomRight());
    QRect imageLabelRect(globalTopLeft, globalBottomRight);
    origin = this->mapFromGlobal(event->globalPos());
    if(insrt){
        if (event->button() == Qt::LeftButton && imageLabelRect.contains(origin)) {
            if(crp_prsd){
                rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
                rubberBand->setGeometry(QRect(origin, QSize()));
                rubberBand->show();
            }
            else{
                if(fltrd){
                    QImage updatedImage(img_in.width, img_in.height, QImage::Format_RGB888);

                    // Iterate through each pixel to set the corresponding pixel in the QImage
                    for (int i = 0; i < img_in.width; i++) {
                        for (int j = 0; j < img_in.height; j++) {
                            // Get the RGB values for the pixel
                            int red = img_in(i, j, 0);
                            int green = img_in(i, j, 1);
                            int blue = img_in(i, j, 2);

                            // Set the pixel in the QImage
                            updatedImage.setPixel(i, j, qRgb(red, green, blue));
                        }
                    }

                    // Calculate the scaled size based on the label's size
                    int h = ui->frame_2->height();
                    int w = ui->frame_2->width();
                    h-=25;
                    double scale = (double)h/img_in.height;
                    fxdSz = QSize(qMin(scale*img_in.width,(double)w-25),h);
                    imgSz = updatedImage.size().scaled(fxdSz,Qt::KeepAspectRatio);
                    QSize scaledSize = imgSz;

                    // Convert the QImage to a QPixmap
                    QPixmap pixmap = QPixmap::fromImage(updatedImage.scaled(scaledSize, Qt::KeepAspectRatio));

                    // Update the label with the QPixmap and keep the label's size fixed
                    ui->image_label->setPixmap(pixmap);
                    ui->image_label->setFixedSize(pixmap.size());
                }
                else{
                    save_change();
                }
                fltrd = !fltrd;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(insrt){
        if(crp_prsd){
            if(rubberBand != NULL){
                QPoint globalTopLeft = ui->image_label->mapToGlobal(ui->image_label->rect().topLeft());
                QPoint globalBottomRight = ui->image_label->mapToGlobal(ui->image_label->rect().bottomRight());
                QRect imageLabelRect(globalTopLeft, globalBottomRight);

                rubberBand->setGeometry(QRect(origin, QPoint(fmax(fmin((int)event->pos().x(),(int)imageLabelRect.right()-2),(int)imageLabelRect.left()+2),fmax(fmin((int)event->pos().y(),(int)imageLabelRect.bottom()-25),(int)imageLabelRect.top()-22))).normalized());
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if(insrt){
        if(crp_prsd){
            if(rubberBand != NULL){
                QPoint globalTopLeft = ui->image_label->mapToGlobal(ui->image_label->rect().topLeft());
                QPoint globalBottomRight = ui->image_label->mapToGlobal(ui->image_label->rect().bottomRight());
                QRect imageLabelRect(globalTopLeft, globalBottomRight);
                QRect dim = rubberBand->geometry();

                int x = fmax(0,dim.left() - imageLabelRect.left());
                int y = fmax(0,dim.top() - (imageLabelRect.top()-22));
                int w = dim.right() - imageLabelRect.left() - x;
                int h = dim.bottom() - (imageLabelRect.top()-22) - y;
                double scalew = imageLabelRect.right() - imageLabelRect.left(), scaleh = imageLabelRect.bottom() - (imageLabelRect.top()-22);
                scalew = img_filter.width/scalew;
                scaleh = img_filter.height/scaleh;
                if(w<=5||h<=5){
                    QMessageBox msg;
                    msg.setIcon(QMessageBox::Information);
                    msg.setText("Invalid Size!!");
                    msg.exec();
                }
                else{
                    imageStack.push(img_filter);
                    img_filter = crop_image((int)(x*scalew), (int)(y*scaleh), (int)(w*scalew), (int)(h*scaleh));

                    save_change();


                    crp_prsd = false;
                }
                rubberBand->hide();
                delete rubberBand;
                rubberBand = NULL;
            }
        }
    }
}

void MainWindow::on_cropImage_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    if(brtns){
        restore();
    }

    crp_prsd = !crp_prsd;
    QMessageBox msgbx;
    msgbx.setIcon(QMessageBox::Information);
    if(crp_prsd)
        msgbx.setText("Crop Activated!\nIf you want to cancel cropping press the button again.");
    else
        msgbx.setText("Crop Deactivated!");
    msgbx.exec();
}

void rotate_image_90deg() {
    // Create a new Image object with dimensions swapped to accommodate rotation.
    Image img_rotated(img_filter.height, img_filter.width);
    // Iterate over the pixels of the original image.
    for (int i = 0; i < img_filter.width; i++) {
        for (int j = 0; j < img_filter.height; j++) {
            // Iterate over the color channels (assuming RGB here).
            for (int k = 0; k < 3; k++) {
                // Assign pixel value from original image to the corresponding position
                // in the rotated image, swapping x and y coordinates.
                img_rotated(j, i, k) = img_filter(i, j, k);
            }
        }
    }
    img_filter = img_rotated;
}

void flip_vertically() {
    // Create a new image to store the vertically flipped image
    Image img_flipped(img_filter.width, img_filter.height);
    // Iterate through each pixel in the image
    for (int j = img_filter.height - 1; j >= 0; j--) {
        for (int i = 0; i < img_filter.width; i++) {
            // Flip the image in the y-direction
            for (int k = 0; k < 3; k++) {
                img_flipped(i, img_filter.height - 1 - j, k) = img_filter(i, j, k);
            }
        }
    }
    img_filter = img_flipped;
}

void MainWindow::on_rotate_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    imageStack.push(img_filter);
    if(brtns){
        restore();
    }

    flip_vertically();
    rotate_image_90deg();

    save_change();
}

int l ;
int colorR;
int colorG;
int colorB;
int l2 ;
int colorR2;
int colorG2;
int colorB2;
int value_Slider;
int qq;
void MainWindow::on_frame_image_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    if(brtns){
        restore();
    }

    // double width;
    QMenu menuresize(this);
    QAction *BasiceFrame = menuresize.addAction("one color frame");
    QAction *fancyFrame = menuresize.addAction("double color frame");
    QAction *blurFrame =  menuresize.addAction("blur frame");
    connect(BasiceFrame, &QAction::triggered, this, [this](){
        while (true) {
            // Create a dialog to host the spin boxes and sliders
            QDialog dialog(this);
            dialog.setWindowTitle(tr("Enter Variables"));

            // Layout for the dialog
            QVBoxLayout layout(&dialog);

            // Create a widget to hold all the elements
            QWidget widget;
            QVBoxLayout widgetLayout(&widget);

            // Create the first spin box
            QLabel label1("Width of frame:");
            QSpinBox spinBox1;
            spinBox1.setMinimum(0); // Set minimum value
            spinBox1.setMaximum(img_filter.width/2);
            widgetLayout.addWidget(&label1);
            widgetLayout.addWidget(&spinBox1);

            // Create the sliders for RGB values
            QLabel rangeR("Range color of red: (0 - 255)");
            QSlider *sliderR = new QSlider(Qt::Horizontal);
            sliderR->setRange(0, 255); // Set the range of the slider
            sliderR->setValue(0); // Set initial value
            sliderR->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeR);
            widgetLayout.addWidget(sliderR);

            QLabel rangeG("Range color of green: (0 - 255)");
            QSlider *sliderG = new QSlider(Qt::Horizontal);
            sliderG->setRange(0, 255); // Set the range of the slider
            sliderG->setValue(0); // Set initial value
            sliderG->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeG);
            widgetLayout.addWidget(sliderG);

            QLabel rangeB("Range color of blue: (0 - 255)");
            QSlider *sliderB = new QSlider(Qt::Horizontal);
            sliderB->setRange(0, 255); // Set the range of the slider
            sliderB->setValue(0); // Set initial value
            sliderB->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeB);
            widgetLayout.addWidget(sliderB);

            imageStack.push(img_filter);
            // Create a QLabel to display the color
            QLabel colorLabel;
            colorLabel.setFixedSize(50, 50); // Set fixed size for the color label

            widgetLayout.addWidget(&colorLabel);

            // Add the widget to the layout
            layout.addWidget(&widget);

            // Add OK and Cancel buttons
            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
            layout.addWidget(&buttonBox);

            // Connect buttons to slots
            connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
            connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

            // Connect slider value change to update the color label
            connect(sliderR, &QSlider::valueChanged, [&]() {
                QColor color(sliderR->value(), sliderG->value(), sliderB->value());
                colorLabel.setStyleSheet(QString("background-color: %1;").arg(color.name()));
            });
            connect(sliderG, &QSlider::valueChanged, [&]() {
                QColor color(sliderR->value(), sliderG->value(), sliderB->value());
                colorLabel.setStyleSheet(QString("background-color: %1;").arg(color.name()));
            });
            connect(sliderB, &QSlider::valueChanged, [&]() {
                QColor color(sliderR->value(), sliderG->value(), sliderB->value());
                colorLabel.setStyleSheet(QString("background-color: %1;").arg(color.name()));
            });

            // Execute the dialog
            if (dialog.exec() == QDialog::Accepted) {
                // Retrieve the values from the spin box and sliders
                l = spinBox1.value();
                colorR = sliderR->value();
                colorG = sliderG->value();
                colorB = sliderB->value();

                // Use the values as needed
                break; // Exit the loop since we have valid input
            } else {
                // User canceled, exit the function
                return;
            }
        }

        // Create a new image for the framed result
        Image framed(img_filter.width + 2 * l, img_filter.height + 2 * l);
        // Fill the frame area with the desired RGB values
        for (int i = 0; i < framed.width; i++) {
            for (int j = 0; j < framed.height; j++) {
                framed(i, j, 0) = colorR;
                framed(i, j, 1) = colorG;
                framed(i, j, 2) = colorB;
            }
        }
        // Copy the original image into the frame area
        for (int i = l; i < l + img_filter.width; i++) {
            for (int j = l; j < l + img_filter.height; j++) {
                for (int k = 0; k < 3; k++) {
                    framed(i, j, k) = img_filter(i - l, j - l, k);
                }
            }
        }
        // Save the framed image and update the input image
        img_filter = framed;
        Image img_resize = img_filter;


        // Now you have valid values for both variables, you can use them as needed
        save_change();


    });
    connect(fancyFrame, &QAction::triggered, this, [this](){
        while (true) {
            // Create a dialog to host the spin boxes and sliders
            QDialog dialog(this);
            dialog.setWindowTitle(tr("Enter Variables"));

            // Layout for the dialog
            QVBoxLayout layout(&dialog);

            // Create a widget to hold all the elements
            QWidget widget;
            QVBoxLayout widgetLayout(&widget);


            // Create the first spin box
            QLabel label1("Width of frame:");
            QSpinBox spinBox1;
            spinBox1.setMinimum(0); // Set minimum value
            spinBox1.setMaximum(9999999);
            widgetLayout.addWidget(&label1);
            widgetLayout.addWidget(&spinBox1);

            // Create the sliders for RGB values
            QLabel rangeR("Range color of red: (0 - 255)");
            QSlider *sliderR = new QSlider(Qt::Horizontal);
            sliderR->setRange(0, 255); // Set the range of the slider
            sliderR->setValue(0); // Set initial value
            sliderR->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeR);
            widgetLayout.addWidget(sliderR);

            QLabel rangeG("Range color of green: (0 - 255)");
            QSlider *sliderG = new QSlider(Qt::Horizontal);
            sliderG->setRange(0, 255); // Set the range of the slider
            sliderG->setValue(0); // Set initial value
            sliderG->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeG);
            widgetLayout.addWidget(sliderG);

            QLabel rangeB("Range color of blue: (0 - 255)");
            QSlider *sliderB = new QSlider(Qt::Horizontal);
            sliderB->setRange(0, 255); // Set the range of the slider
            sliderB->setValue(0); // Set initial value
            sliderB->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeB);
            widgetLayout.addWidget(sliderB);

            // Create a QLabel to display the color
            QLabel colorLabel;
            colorLabel.setFixedSize(50, 50); // Set fixed size for the color label

            widgetLayout.addWidget(&colorLabel);

            // Add the widget to the layout
            layout.addWidget(&widget);

            // Add OK and Cancel buttons
            // QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
            // layout.addWidget(&buttonBox);

            // Connect buttons to slots


            // Connect slider value change to update the color label
            connect(sliderR, &QSlider::valueChanged, [&]() {
                QColor color(sliderR->value(), sliderG->value(), sliderB->value());
                colorLabel.setStyleSheet(QString("background-color: %1;").arg(color.name()));
            });
            connect(sliderG, &QSlider::valueChanged, [&]() {
                QColor color(sliderR->value(), sliderG->value(), sliderB->value());
                colorLabel.setStyleSheet(QString("background-color: %1;").arg(color.name()));
            });
            connect(sliderB, &QSlider::valueChanged, [&]() {
                QColor color(sliderR->value(), sliderG->value(), sliderB->value());
                colorLabel.setStyleSheet(QString("background-color: %1;").arg(color.name()));
            });

            // Create a widget to hold all the elements
            // Create the first spin box
            QLabel label2("Width of frame:");
            QSpinBox spinBox2;
            spinBox2.setMinimum(0); // Set minimum value
            spinBox2.setMaximum(999999999);
            widgetLayout.addWidget(&label2);
            widgetLayout.addWidget(&spinBox2);

            // Create the sliders for RGB values
            QLabel rangeR2("Range color of red: (0 - 255)");
            QSlider *sliderR2 = new QSlider(Qt::Horizontal);
            sliderR2->setRange(0, 255); // Set the range of the slider
            sliderR2->setValue(0); // Set initial value
            sliderR2->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeR2);
            widgetLayout.addWidget(sliderR2);

            QLabel rangeG2("Range color of green: (0 - 255)");
            QSlider *sliderG2 = new QSlider(Qt::Horizontal);
            sliderG2->setRange(0, 255); // Set the range of the slider
            sliderG2->setValue(0); // Set initial value
            sliderG2->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeG2);
            widgetLayout.addWidget(sliderG2);

            QLabel rangeB2("Range color of blue: (0 - 255)");
            QSlider *sliderB2 = new QSlider(Qt::Horizontal);
            sliderB2->setRange(0, 255); // Set the range of the slider
            sliderB2->setValue(0); // Set initial value
            sliderB2->setMinimumWidth(200);
            widgetLayout.addWidget(&rangeB2);
            widgetLayout.addWidget(sliderB2);

            imageStack.push(img_filter);
            // Create a QLabel to display the color
            QLabel colorLabel2;
            colorLabel2.setFixedSize(50, 50); // Set fixed size for the color label

            widgetLayout.addWidget(&colorLabel2);

            // Add the widget to the layout
            layout.addWidget(&widget);

            // Add OK and Cancel buttons
            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
            layout.addWidget(&buttonBox);

            // Connect buttons to slots
            connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
            connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

            // Connect slider value change to update the color label
            connect(sliderR2, &QSlider::valueChanged, [&]() {
                QColor color2(sliderR2->value(), sliderG2->value(), sliderB2->value());
                colorLabel2.setStyleSheet(QString("background-color: %1;").arg(color2.name()));
            });
            connect(sliderG2, &QSlider::valueChanged, [&]() {
                QColor color2(sliderR2->value(), sliderG2->value(), sliderB2->value());
                colorLabel2.setStyleSheet(QString("background-color: %1;").arg(color2.name()));
            });
            connect(sliderB2, &QSlider::valueChanged, [&]() {
                QColor color2(sliderR2->value(), sliderG2->value(), sliderB2->value());
                colorLabel2.setStyleSheet(QString("background-color: %1;").arg(color2.name()));
            });

            // Execute the dialog
            if (dialog.exec() == QDialog::Accepted) {
                // Retrieve the values from the spin box and sliders
                l = spinBox1.value();
                colorR = sliderR->value();
                colorG = sliderG->value();
                colorB = sliderB->value();
                l2 = spinBox2.value();
                colorR2 = sliderR2->value();
                colorG2 = sliderG2->value();
                colorB2 = sliderB2->value();

                // Use the values as needed
                break; // Exit the loop since we have valid input
            } else {
                // User canceled, exit the function
                return;
            }
        }
        int z = l/2;
        // Create a new image for the framed result
        Image framed(img_filter.width + 2 * l, img_filter.height + 2 * l);
        // Fill the frame area with the desired RGB values
        for (int i = 0; i < framed.width; i++) {
            for (int j = 0; j < framed.height; j++) {
                framed(i, j, 0) = colorR;
                framed(i, j, 1) = colorG;
                framed(i, j, 2) = colorB;
            }
        }
        for (int i = z; i < framed.width - z; i++) {
            for (int j = z; j < framed.height - z; j++) {
                framed(i, j, 0) = colorR2;
                framed(i, j, 1) = colorG2;
                framed(i, j, 2) = colorB2;
            }
        }
        // Copy the original image into the frame area
        for (int i = l; i < l + img_filter.width; i++) {
            for (int j = l; j < l + img_filter.height; j++) {
                for (int k = 0; k < 3; k++) {
                    framed(i, j, k) = img_filter(i - l, j - l, k);
                }
            }
        }
        // Save the framed image and update the input image
        img_filter = framed;
        Image img_resize = img_filter;


        // Now you have valid values for both variables, you can use them as needed
        save_change();



    });
    connect(blurFrame, &QAction::triggered, this, [this](){
        while (true) {
            // Create a dialog to host the spin boxes and sliders
            QDialog dialog(this);
            dialog.setWindowTitle(tr("Enter Variables"));

            // Layout for the dialog
            QVBoxLayout layout(&dialog);

            // Create a widget to hold all the elements
            QWidget widget;
            QVBoxLayout widgetLayout(&widget);

            // Create the first spin box
            QLabel label1("Width of frame:");
            QSpinBox spinBox1;
            spinBox1.setMinimum(0); // Set minimum value
            spinBox1.setMaximum(img_filter.width/2);
            widgetLayout.addWidget(&label1);
            widgetLayout.addWidget(&spinBox1);

            // Create the sliders for RGB values
            QLabel widthblur("Range color of red: (3 - 100)");
            QSlider *sliderblur = new QSlider(Qt::Horizontal);
            sliderblur->setRange(0, 100); // Set the range of the slider
            sliderblur->setValue(0); // Set initial value
            sliderblur->setMinimumWidth(200);
            widgetLayout.addWidget(&widthblur);
            widgetLayout.addWidget(sliderblur);


            imageStack.push(img_filter);

            // Create a QLabel to display the color
            QLabel valueslider;
            widthblur.setFixedSize(30, 30); // Set fixed size for the color label

            widgetLayout.addWidget(&valueslider);

            // Add the widget to the layout
            layout.addWidget(&widget);

            // Add OK and Cancel buttons
            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
            layout.addWidget(&buttonBox);

            // Connect buttons to slots
            connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
            connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

            // Connect slider value change to update the color label
            connect(sliderblur, &QSlider::valueChanged, [&]() {
                QString valueText = QString("R: %1").arg(sliderblur->value());
                widthblur.setText(valueText);
            });


            // Execute the dialog
            if (dialog.exec() == QDialog::Accepted) {
                // Retrieve the values from the spin box and sliders
                qq = spinBox1.value();
                value_Slider = sliderblur->value();


                // Use the values as needed
                break; // Exit the loop since we have valid input
            } else {
                // User canceled, exit the function
                return;
            }
        }
        // blurImage(value_Slider);
        Image blr(img_filter);
        blurImage(value_Slider);

        int w = img_filter.width, h = img_filter.height;
        img_filter = resize1(img_filter,2*qq + w, 2*qq + h);
        for (int i = qq; i < qq + blr.width; i++) {
            for (int j = qq; j < qq + blr.height; j++) {
                for (int k = 0; k < 3; k++) {
                    img_filter(i, j, k) = blr(i - qq, j - qq, k);
                }
            }
        }
        Image img_resize = img_filter;


        // Now you have valid values for both variables, you can use them as needed
        save_change();

    });
    menuresize.exec(ui->frame_image->mapToGlobal(QPoint(0, ui->frame_image->height())));
}

Image  img_one,img_two; // Variables to store the two images to be merged
int max_width, max_height, min_width, min_height;
void merge_images(Image img_first, Image img_second) {
    // Create a new image for merging with dimensions equal to the minimum of the two input images
    Image img_megred(qMin(img_first.width, img_second.width), qMin(img_first.height, img_second.height));
    // Iterate through each pixel in the merged image
    for (int i = 0; i < qMin(img_first.width, img_second.width); i++) {
        for (int j = 0; j < qMin(img_first.height, img_second.height); j++) {
            // Average the RGB values of corresponding pixels from both images and assign to the merged image
            for (int k = 0; k < 3; k++) {
                img_megred(i, j, k) = (img_first(i, j, k) + img_second(i, j, k)) / 2;
            }
        }
    }
    img_out = img_megred;
}

void MainWindow::mergeselect() {
    QString mergeName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    // Check if a file is selected
    if (!mergeName.isEmpty()) {
        try {
            // Load the image from file
            QImage mergeQimage(mergeName);

            // Check if the image is valid
            if (!mergeQimage.isNull()) {

                // Create and configure the dialog
                QDialog dialog(this);
                dialog.setWindowTitle(tr("Enter Variables"));

                QVBoxLayout layout(&dialog);
                QWidget widget;
                QVBoxLayout widgetLayout(&widget);

                QLabel mergeIlabel;
                mergeIlabel.setFixedSize(500, 500);
                widgetLayout.addWidget(&mergeIlabel);
                layout.addWidget(&widget);

                QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
                layout.addWidget(&buttonBox);

                // Connect buttons to slots
                connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
                connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

                // Display the loaded image
                QSize imageSize = ui->image_label->size();
                QSize scaledSize = mergeQimage.size().scaled(imageSize, Qt::KeepAspectRatio);
                QPixmap pixmap = QPixmap::fromImage(mergeQimage.scaled(scaledSize, Qt::KeepAspectRatio));
                mergeIlabel.setPixmap(pixmap);
                mergeIlabel.setFixedSize(pixmap.size());


                // Execute the dialog and handle user input
                if (dialog.exec() == QDialog::Accepted) {
                    // Handle accepted dialog
                    // Optionally, you can retrieve any user input or perform further processing here
                    megred.loadNewImage(mergeName.toStdString());
                    mrg = true;
                }
                else {
                    // Handle rejected dialog
                    // For example, reset img_filter to its initial state
                    //megred = img_out;
                    mrg = false;
                    return;
                }


            } else {
                // Display an error message if the image cannot be loaded
                QMessageBox::warning(this, tr("Error"), tr("Failed to load image!"));
            }
        } catch (const std::exception& e) {
            // Catch any exceptions and display an error message
            QMessageBox::warning(this, tr("Error"), tr("An error occurred: ") + QString::fromStdString(e.what()));
        }
      }
    else{
        mrg = false;
    }

}




void MainWindow::on_megre_Image_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    if(brtns){
        restore();
    }

 // Variables to store dimensions of the images

    QMenu mergeMenu (this);
    QAction *ResizeToSmall = mergeMenu.addAction("Resize To Smallest dimention ");
    QAction *ResizeToBig = mergeMenu.addAction("Resize To Biggest dimention");
    QAction *commanArea =  mergeMenu.addAction("Reise To Comman Area ");
    connect(ResizeToSmall, &QAction::triggered, this, &MainWindow::mergeselect);
    connect(ResizeToBig, &QAction::triggered, this, &MainWindow::mergeselect);
    connect(commanArea, &QAction::triggered, this, &MainWindow::mergeselect);



    connect(ResizeToSmall, &QAction::triggered, this, [this](){
        if(mrg){
            img_one = img_filter;
            img_two = megred;

            if (img_one.width > img_two.width) {
                max_width = img_one.width;
                min_width = img_two.width;
            } else {
                max_width = img_two.width;
                min_width = img_one.width;
            }

            if (img_one.height > img_two.height) {
                max_height = img_one.height;
                min_height = img_two.height;
            } else {
                max_height = img_two.height;
                min_height = img_one.height;
            }
            img_one = resize1(img_one, min_width, min_height);
            img_two = resize1(img_two, min_width, min_height);

            imageStack.push(img_filter);
            merge_images(img_one, img_two);
            img_filter = img_out;

            // Convert the merged Image to QImage
            save_change();
        }
    });
    connect(ResizeToBig, &QAction::triggered, this, [this](){
        if(mrg){
            img_one = img_filter;
            img_two =  megred;

            if (img_one.width > img_two.width) {
                max_width = img_one.width;
                min_width = img_two.width;
            } else {
                max_width = img_two.width;
                min_width = img_one.width;
            }

            if (img_one.height > img_two.height) {
                max_height = img_one.height;
                min_height = img_two.height;
            } else {
                max_height = img_two.height;
                min_height = img_one.height;
            }
            // Implement resize1 function to resize the image
            img_one = resize1(img_one, max_width, max_height);
            img_two = resize1(img_two, max_width, max_height);

            imageStack.push(img_filter);
            merge_images(img_one, img_two);
            img_filter = img_out;

            // Convert the merged Image to QImage
            save_change();
        }

    });
    connect(commanArea, &QAction::triggered, this, [this](){
        if(mrg){
            img_one = img_filter;
            img_two =  megred;
            imageStack.push(img_filter);
            merge_images(img_one, img_two);
            img_filter = img_out;

            // Convert the merged Image to QImage
            save_change();
        }


    });
    mergeMenu.exec(ui->megre_Image->mapToGlobal(QPoint(0, ui->megre_Image->height())));
}
void MainWindow :: undoShortcut(){
    if (!imageStack.empty()) {
        redoStack.push(img_filter);
        // Pop the last image state from the stack
        img_filter = imageStack.top();
        imageStack.pop();
       save_change();
    }
}
void MainWindow::redoOperation()
{
    // Check if there are any operations to redo
    if (!redoStack.empty()) {
        // Push the current image state onto the undo stack
        imageStack.push(img_filter);

        // Pop the last image state from the redo stack
        img_filter = redoStack.top();
        redoStack.pop();
        save_change();
        // Update the displayed image
    }
}
Image brt = img_filter;
void MainWindow::on_editBrightness_clicked()
{
    if(!insrt){
        QMessageBox :: warning(this,"No Image!","Please insert image first.");
        return;
    }
    brtns = !brtns;
    if(brtns){
        QImage updatedImage(img_filter.width, img_filter.height, QImage::Format_RGB888);

        // Iterate through each pixel to set the corresponding pixel in the QImage
        for (int i = 0; i < img_filter.width; i++) {
            for (int j = 0; j < img_filter.height; j++) {
                // Get the RGB values for the pixel
                int red = img_filter(i, j, 0);
                int green = img_filter(i, j, 1);
                int blue = img_filter(i, j, 2);

                // Set the pixel in the QImage
                updatedImage.setPixel(i, j, qRgb(red, green, blue));
            }
        }

        // Calculate the scaled size based on the label's size
        int h = ui->frame_2->height();
        int w = ui->frame_2->width();
        ui->frame_2->setFixedHeight(h-35);
        //ui->frame_2->setFixedWidth(w-35);
        h-=60;
        w-=25;
        double scale = (double)h/img_filter.height;
        fxdSz = QSize(qMin( scale*img_filter.width,(double)w),h);
        imgSz = updatedImage.size().scaled(fxdSz, Qt::KeepAspectRatio);
        QSize scaledSize = imgSz;

        // Convert the QImage to a QPixmap
        QPixmap pixmap = QPixmap::fromImage(updatedImage.scaled(scaledSize, Qt::KeepAspectRatio));

        // Update the label with the QPixmap and keep the label's size fixed
        ui->image_label->setPixmap(pixmap);
        ui->image_label->setFixedSize(pixmap.size());
    }
    else{
        QImage updatedImage(img_filter.width, img_filter.height, QImage::Format_RGB888);

        // Iterate through each pixel to set the corresponding pixel in the QImage
        for (int i = 0; i < img_filter.width; i++) {
            for (int j = 0; j < img_filter.height; j++) {
                // Get the RGB values for the pixel
                int red = img_filter(i, j, 0);
                int green = img_filter(i, j, 1);
                int blue = img_filter(i, j, 2);

                // Set the pixel in the QImage
                updatedImage.setPixel(i, j, qRgb(red, green, blue));
            }
        }

        // Calculate the scaled size based on the label's size
        int h = ui->frame_2->height();
        int w = ui->frame_2->width();
        ui->frame_2->setFixedHeight(h+35);
        //ui->frame_2->setFixedWidth(w+35);
        h+=10;
        w-=25;
        double scale = (double)h/img_filter.height;
        fxdSz = QSize(qMin( scale*img_filter.width,(double)w),h);
        imgSz = updatedImage.size().scaled(fxdSz, Qt::KeepAspectRatio);
        QSize scaledSize = imgSz;

        // Convert the QImage to a QPixmap
        QPixmap pixmap = QPixmap::fromImage(updatedImage.scaled(scaledSize, Qt::KeepAspectRatio));

        // Update the label with the QPixmap and keep the label's size fixed
        ui->image_label->setPixmap(pixmap);
        ui->image_label->setFixedSize(pixmap.size());
    }

    ui->brightness->setMinimum(-255);
    ui->brightness->setMaximum(255);
    ui->brightness->setValue(0);
    ui->brightness->setVisible(brtns);
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    if(brtns){
        msg.setText("Brightness Activated!\nToggle the slider under the image\nand press the button to apply changes to image.");
        brt = img_filter;
    }
    else{
        msg.setText("Changes applied to image!");
        imageStack.push(img_filter);
        img_filter = brt;
        save_change();
    }
    msg.exec();
}

void MainWindow::on_brightness_sliderMoved()
{
    double val;
    val = ui->brightness->value();
    val/=100.0;
    brt = img_filter;
    for (int i = 0; i < brt.width; i++) {
        for (int j = 0; j < brt.height; j++) {
            for (int k = 0; k < 3; k++) {
                brt(i, j, k) = qMax(qMin((int)((1+val)*img_filter(i,j,k)),255),0);
                //brt(i,j,k) = qMax(qMin((int)(img_filter(i,j,k)+val),255),0);
            }
        }
    }

    QImage updatedImage(brt.width, brt.height, QImage::Format_RGB888);
    // Iterate through each pixel to set the corresponding pixel in the QImage
    for (int i = 0; i < brt.width; i++) {
        for (int j = 0; j < brt.height; j++) {
            // Get the RGB values for the pixel
            int red = brt(i, j, 0);
            int green = brt(i, j, 1);
            int blue = brt(i, j, 2);
            // Set the pixel in the QImage
            updatedImage.setPixel(i, j, qRgb(red, green, blue));
        }
    }
    // Calculate the scaled size based on the label's size
    imgSz = updatedImage.size().scaled(fxdSz, Qt::KeepAspectRatio);
    QSize scaledSize = imgSz;
    // Convert the QImage to a QPixmap
    QPixmap pixmap = QPixmap::fromImage(updatedImage.scaled(scaledSize, Qt::KeepAspectRatio));
    // Update the label with the QPixmap and keep the label's size fixed
    ui->image_label->setPixmap(pixmap);
    ui->image_label->setFixedSize(pixmap.size());

}


