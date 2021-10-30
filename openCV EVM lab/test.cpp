#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#include <ctime>

using namespace std;
using namespace cv;

int main() {
	VideoCapture cap(1);
	Mat img;

	CascadeClassifier faceCascade;
	faceCascade.load("haarcascade_frontalface_default.xml");
	vector<Rect> faces;
	short y_ball = -8, x_ball = rand() % 640;
	uint tl = 0, br = 0;
	size_t i;
	clock_t start, end;
	double sec;
	int key;
	while (true) {
		start = clock();
		cap.read(img);	
		flip(img, img, 1);
		faceCascade.detectMultiScale(img, faces, 1.5, 2);	
		for (size_t i = 0; i < faces.size(); ++i) {
			//rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 1);
			if (faces[i].tl().x <= x_ball && faces[i].br().x >= x_ball && faces[i].br().y >= y_ball && faces[i].tl().y <= y_ball)
				y_ball = 488;
		}
		if (y_ball < 487)
			circle(img, { x_ball , y_ball += 10 }, 25, Scalar(rand() % 256, rand() % 256, rand() % 256), FILLED);
		else {
			y_ball = -8;
			x_ball = rand()% 640;
		}
		end = clock();
		sec = (double(end) - double(start))/double(CLOCKS_PER_SEC);
		sec = 1 / double(sec);
		putText(img, "FPS:" + to_string(sec), { 400,20 }, FONT_HERSHEY_DUPLEX, 0.5, (255, 0, 255));
		imshow("Image", img);
		key = waitKey(30);
		if (key == 'q' or key == 27)
			break;
	}
	return 0;
}