#include <iostream>
#include <cmath>
#include <string>
#include <regex>


inline float cmtoinch(float cm) {
    return cm / 2.54;
}

inline float inchtocm(float inch) {
	return inch * 2.54;
}

float get_height(float diag, float ratio) {
    /*
     * Return height in the same unit as diag
     */
    
    //(ratio * height)^2 + height^2 = diag^2
    //(ratio^2 + 1) height^2 = diag^2
    return std::sqrt( diag * diag / (ratio * ratio + 1) );
}

int get_px_height(int wratio, int hratio, int px_width) {
	return px_width * hratio / wratio;
}

int get_px_width(int wratio, int hratio, int px_height) {
	return px_height * wratio / hratio;
}

float get_ppi(float height, int nlines) {
	return nlines / height;
}

int main(int argc, char *argv[]) {

	int width_prime = -1;
	int height_prime = -1;
	float diag = -1.0f;
	int px_height = -1;

	bool error = false;

	if (argc > 3) {
		char *cargv = argv[1];
		std::string input(cargv);

		//std::cout << input << std::endl;
		std::smatch m;
		std::regex e("([^ ]+):([^ ]+)");

		/*
		while (std::regex_search(input, m, e)) {
		//for (auto x : m) std::cout << x << " ";
		std::cout << std::stoi(m[1]) << " " << std::stoi(m[2]);
		break;
		}
		*/

		if (std::regex_search(input, m, e)) {
			width_prime = std::stoi(m[1]);
			height_prime = std::stoi(m[2]);
		}
		else {
			std::cout << "Incorrect format. Supply aspect ratio as e.g. '16:9'.";
			error = true;
		}

		cargv = argv[2];
		diag = std::stof(std::string(cargv));

		cargv = argv[3];
		px_height = std::stoi(std::string(cargv));

	}
	else {
		error = true;
		std::cout << "Please provide (in this order): aspect ratio (e.g. 4:3), diagonal (inches), number of pixel lines (e.g. 1080).";
	}

	if (!error) {
		std::cout << "Screen diagonal (inch): " << diag << std::endl;
		std::cout << "Screen aspect ratio:    " << width_prime << ":" << height_prime << std::endl;
		std::cout << "Height (pixels):        " << px_height << std::endl;
		std::cout << "Screen resolution:      " << get_px_width(width_prime, height_prime, px_height) << "x" << px_height << std::endl;

		float inch_height = get_height(diag, (float) width_prime / height_prime);
		std::cout << "Screen height (inch):   " << inch_height << std::endl;
		std::cout << "Screen height (cm):     " << inchtocm(inch_height) << std::endl;

		std::cout << "Pixel density (ppi):    " << get_ppi(inch_height, px_height);
	}

}