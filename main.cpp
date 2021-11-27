#include <QCoreApplication>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/opencv_modules.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/opencv_modules.hpp>
#include <opencv4/opencv2/core/cuda.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
//=====================================================================================================
QStringList GetAllFiles(QString path,QString aliasPath="")
{
    QDir directory(path);
    int i=0;
    QStringList result;
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.jpg" << "*.PNG"<< "*.bmp"<< "*.BMP" << "*.JPG",QDir::Files);
    foreach (QString item, images) {
        if(aliasPath=="")
        {
         result.append(path+"/"+item);
        }

        else {
            result.append(aliasPath+"/"+item);
        }
       }
    return  result;
}

void Mat2Bin(cv::Mat image,QString fileName)
{

    QFile mfile(fileName);
    mfile.open(QFile::ReadWrite);
    QByteArray qData;

    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
           cv::Vec3b pixel=image.at<cv::Vec3b>(i, j);
           qData.append(pixel[0]);
           qData.append(pixel[1]);
           qData.append(pixel[2]);

        }
    }
    mfile.write(qData);
    mfile.close();

}
//===========================================================
cv::Mat LineCamSim(cv::Mat image,int ratio)
{
    cv::Mat result = cv::Mat::zeros(cv::Size(image.cols, image.rows*ratio), CV_8UC3);
    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
            cv::Mat temp= image.clone();
            cv::Vec3b pixel=temp.at<cv::Vec3b>(i, j);

            for(int r=0;r<ratio;r++)
            {
                result.at<cv::Vec3b>(i*ratio+r, j) =pixel;

            }
        }


    }
    return result;
}
//===========================================================
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc<2)
    {
        qDebug()<<"please pass input and output folder name as argument\n"
                  "example: ./LinecamSim.sh /inputpath /outputpath";
        return 0;
    }
    QStringList files=GetAllFiles(argv[1]);
QDir dir;
    dir.mkdir(argv[2]);
for(int i=0;i<files.count();i++)
{
    cv::Mat image=cv::imread(files[i].toStdString());
    QString name=argv[2];
    name+="//"+QString::number(i)+".png";
    cv::imwrite(name.toStdString(),LineCamSim(image,5));
}
    return  0;
}
