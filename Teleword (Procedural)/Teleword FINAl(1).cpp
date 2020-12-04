#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <Windows.h>

using namespace std;

int num[15][15];

int gridout(char grid[][15]) {
	int i = 0;
	char twords[225];
	ifstream myfile("C:\\Users\\l190947\\Downloads\\hw4\\hw4\\sample puzzles\\teleword_1.txt");

	if (myfile.fail()) { cout << "file not open"; }
	else { cout << "file open"; }
	cout << endl;

	while (i < 225) {
		myfile >> twords[i];
		i++;
	}

	i = 0;
	int j = 0, k = 0;


	for (i = 0;i < 15;i++) {
		for (j = 0;j < 15;j++) {

			grid[i][j] = twords[k];
			k++;
		}
	}
	i = 0;
	for (i = 0;i < 15;i++) {
		for (j = 0;j < 15;j++) {

			cout << setw(3) << grid[i][j];
		}
		cout << endl;

	}
	return 0;
}

void numbergrid (int numgrid [][15]) {
	for (int i=0;i<15;i++){

		for (int j=0;j<15;j++) {

			numgrid[i][j]=0;
		}

	}

	for (int i=0;i<15;i++){

		for (int j=0;j<15;j++) {

			cout << setw(3) << numgrid[i][j];
		}
		cout << endl;
	}
}

int pnumgrid(int numgrid[][15]) {

	for (int i=0;i<15;i++){

		for (int j=0;j<15;j++) {

			cout << setw(3) << numgrid[i][j];
		}
		cout << endl;
	}
	return 0;
}

void gridcopy(char grid[][15]) {

	int i = 0;
	char twords[225];
	ifstream myfile("C:\\Users\\l190947\\Downloads\\hw4\\hw4\\sample puzzles\\teleword_1.txt");

	if (myfile.fail()) { cout << "file not open"; }
	else { cout << "file open"; }
	cout << endl;

	while (i < 225) {
		myfile >> twords[i];
		i++;
	}

	i = 0;
	int j = 0, k = 0;


	for (i = 0;i < 15;i++) {
		for (j = 0;j < 15;j++) {

			grid[i][j] = twords[k];
			k++;

		}

	}
}

int ansinput(char ans[]) {

	ifstream answers("C:\\Users\\l190947\\Downloads\\hw4\\hw4\\sample puzzles\\teleword_1.txt");

	bool dot = false;
	int i = 0;
	char temp;
	int k = 1;

	while (!dot) {

		answers >> temp;
		k++;

		if (temp == '.') {
			dot = true;
		}

		if (k > 226) {
			ans[i] = temp;
			i++;
		}
	}
	int x = 0;

	cout << endl;
	while (x < i) {

		cout << ans[x];
		x++;
	}

	cout << endl;
	return 0;
}

bool rhsearch(char grid[][15], char temp[],  int wlcount, char gridc[][15], int numgrid[][15]) {

	int i = 0, z, k, a = 0, h = 0, f = 0, g = 0, d = 0, u = 0, hcount;
	int wfcount = 0, chk = 0;
	char ansfound[225];
	bool comma = false, fd = false, firstMatch = true, dot = false;
	bool lastword = false;
	int p = 0;
	bool nSame = false;
	bool wordfound = false;

    for (f = 0;f < 15;f++) {
		for (i = 0;i < 15;i++) {
			int y = int(temp[d]);
			int x = int(grid[f][i] + 32);
			if (temp[d] == grid[f][i] || x == y)
			{

				if (firstMatch) { a = i; }
				firstMatch = false;
				fd = true;
				d++;
				wfcount++;

			}
			else if (temp[d] != grid[f][i] && !fd || x != y && !fd) {

				d = 0;
				wfcount = 0;
				firstMatch = true;
				int y = int(temp[d]);
				int x = int(grid[f][i] + 32);
				if (temp[d] == grid[f][i] || x == y) {
					d++;
					wfcount++;
					firstMatch = true;
					if (firstMatch) { a = i; }
					firstMatch = false;
				}
			}
			if (wfcount == wlcount) {
				h = h + 1;
				p = 0;
				wordfound = true;
				comma = false;
				if (lastword) { dot = true; }

				while (a <= i) {
					ansfound[u] = grid[f][a];
					u++;
					gridc[f][a] = '.';
					numgrid[f][a]=numgrid[f][a]+1;
					a++;
				}
			}



			fd = false;
		}

		i = 0;
		
	}

	i = 0;
	int j = 0;

	i = 0;

	while (i < u) {

		cout << ansfound[i] << " ";
		i++;
	}
	if (wordfound) {

		for (int i = 0;i < 15;i++) {

			for (int j = 0;j < 15;j++) {

				cout << setw(3) << gridc[i][j];

			}

			cout << endl;

		}	
	
	}
		cout << endl;

		if (wordfound) {
			return 1;
		}
	
	else {
		return 0;
	}
}

bool upsearch(char grid[][15], char temp[],  int wlcount, char gridc[][15], int numgrid[][15]) {



	int i = 0, z, k, a = 0, h = 0, f = 0, g = 0, d = 0, u = 0, hcount;
	int  wfcount = 0, chk = 0;
	char ansfound[225];
	bool comma = false, wordfound = false, fd = false, firstMatch = true, dot = false;
	bool lastword = false;
	int p = 0;
	bool nSame = false;


	
	for (i = 0;i < 15;i++) {
	
			for (f = 14;f >= 0;f--) {
			int y = int(temp[d]);
			int x = int(grid[f][i] + 32);
			if (temp[d] == grid[f][i] || x == y)
			{


				if (firstMatch) { a = f; }
				firstMatch = false;
				fd = true;
				d++;
				wfcount++;

			}


			else if (temp[d] != grid[f][i] && !fd || x != y && !fd) {

				d = 0;
				wfcount = 0;
				firstMatch = true;
				int y = int(temp[d]);
				int x = int(grid[f][i] + 32);
				if (temp[d] == grid[f][i] || x == y) {

                    d++;
					wfcount++;
					firstMatch = true;
					if (firstMatch) { a = f; }
					firstMatch = false;
				}
			}


			if (wfcount == wlcount) {
				h = h + 1;
				p = 0;
				wordfound = true;
				comma = false;

				if (lastword) { dot = true; }

				while (a >= f) {
					ansfound[u] = grid[a][i];
					u++;
					gridc[a][i] = '.';
					numgrid[a][i]= numgrid[a][i]+1;


					a--;
				}
			}

			fd = false;
		}

		f = 14;
		
	}

	i = 0;
	
	cout << wlcount;
	while (i < u) {

		cout << ansfound[i] << " ";
		i++;
	}
	if (wordfound) {
		for (int i = 0;i < 15;i++) {

			for (int j = 0;j < 15;j++) {

				cout << setw(3) << gridc[i][j];

			}
			cout << endl;
		}

		return 1;
	}
	else {
		return 0;
	}


}

bool dosearch(char grid[][15], char temp[], int wlcount, char gridc[][15], int numgrid[][15]) {

	int i = 0, z, k, a = 0, h = 0, f = 0, g = 0, d = 0, u = 0, hcount;
	int wfcount = 0, chk = 0;
	char ansfound[225];
	bool comma = false, wordfound = false, fd = false, firstMatch = true, dot = false;
	bool lastword = false;
	int p = 0;
	bool nSame = false;



	for (i = 0;i < 15;i++) {

		for (f = 0;f < 15;f++) {

			int y = int(temp[d]);
			int x = int(grid[f][i] + 32);
			if (temp[d] == grid[f][i] || x == y)
			{
				if (firstMatch) { a = f; }
				firstMatch = false;
				fd = true;
				d++;
				wfcount++;

			}


			else if (temp[d] != grid[f][i] && !fd || x != y && !fd) {

				d = 0;
				wfcount = 0;
				firstMatch = true;
				int y = int(temp[d]);
				int x = int(grid[f][i] + 32);
				if (temp[d] == grid[f][i] || x == y) {
					d++;
					wfcount++;
					firstMatch = true;
					if (firstMatch) { a = f; }
					firstMatch = false;
				}
			}


			if (wfcount == wlcount) {
				h = h + 1;
				p = 0;
				wordfound = true;
				comma = false;
				if (lastword) { dot = true; }

				while (a <= f) {


					ansfound[u] = grid[a][i];
					u++;
					gridc[a][i] = '.';
					numgrid[a][i]= numgrid[a][i]+1;
					a++;
				}
			}
			fd = false;
		}

		f = 0;
	}


	
	cout << wlcount;
	i = 0;

	while (i < u) {

		cout << ansfound[i] << " ";
		i++;
	}


	if (wordfound) {
		for (int i = 0;i < 15;i++) {

			for (int j = 0;j < 15;j++) {

				cout << setw(3) << gridc[i][j];
			}

			cout << endl;

		}
		return 1;
	}
	else {
		return 0;
	}


}

bool lhsearch(char grid[][15], char temp[], int wlcount, char gridc[][15], int numgrid[][15]) {

	int i = 0, z, k, a = 0, h = 0, f = 0, g = 0, d = 0, u = 0, hcount;
	int wfcount = 0, chk = 0;
	char ansfound[225];
	bool comma = false, wordfound = false, fd = false, firstMatch = true, dot = false;
	bool lastword = false;
	int p = 0;
	bool nSame = false;
	
	for (f = 0;f < 15;f++) {


		for (i = 14;i >= 0;i--) {


			int y = int(temp[d]);
			int x = int(grid[f][i] + 32);


			if (temp[d] == grid[f][i] || x == y)
			{
				if (firstMatch) { a = i; }

				firstMatch = false;
				fd = true;
				d++;
				wfcount++;

			}


			else if (temp[d] != grid[f][i] && !fd || x != y && !fd) {

				d = 0;
				wfcount = 0;
				firstMatch = true;
				int y = int(temp[d]);
				int x = int(grid[f][i] + 32);

				if (temp[d] == grid[f][i] || x == y) {
					d++;

					wfcount++;

					firstMatch = true;
					if (firstMatch) { a = i; }
					firstMatch = false;
				}
			}


			if (wfcount == wlcount) {
				h = h + 1;
				p = 0;
				wordfound = true;
				comma = false;
				if (lastword) { dot = true; }

				while (a >= i) {

					ansfound[u] = grid[f][a];
					u++;
					gridc[f][a] = '.';
					numgrid[f][a]= numgrid[f][a]+1;

					a--;
				}
			}



			fd = false;
		}
i = 14;
	}

	i = 0;
	int j = 0;

	cout << wlcount;

	i = 0;

	while (i < u) {

		cout << ansfound[i] << " ";
		i++;
	}


	if (wordfound) {
		for (int i = 0;i < 15;i++) {

			for (int j = 0;j < 15;j++) {

				cout << setw(3) << gridc[i][j];

			}

			cout << endl;

		}
		return 1;

	}
	else {
		return 0;
	}

}


bool drsearch(char grid[][15], char temp[], int wlcount, char gridc[][15], int numgrid[][15]) {

	int i = 0, z, k, a = 0, h = 0, f = 0, g = 0, d = 0, u = 0, hcount;
	int  wfcount = 0, chk = 0;
	char ansfound[225];
	bool comma = false, wordfound = false, fd = false, firstMatch = true, dot = false;
	bool lastword = false;
	int p = 0;
	bool nSame = false;
	int b = 0;

	for (g = 0;g < 15;g++) {

        for (int m = 0;m < 15;m++) {
			f = m;
			i = g;

			while (i<15 && f<15) {

				int y = int(temp[d]);
				int x = int(grid[i][f] + 32);

				if (temp[d] == grid[i][f] || x == y)
				{

					if (firstMatch) {
						a = i;
						b = f;
					}

					firstMatch = false;
					fd = true;
					d++;
					wfcount++;

				}


				else if (temp[d] != grid[i][f] && !fd || x != y && !fd) {

					d = 0;

					wfcount = 0;

					firstMatch = true;

					int y = int(temp[d]);

					int x = int(grid[i][f] + 32);

					if (temp[d] == grid[i][f] || x == y) {
						d++;
						wfcount++;
						firstMatch = true;
						if (firstMatch) {
							a = i;
							b = f;
						}
						firstMatch = false;
					}
				}


				if (wfcount == wlcount) {
					h = h + 1;

					p = 0;

					wordfound = true;
					comma = false;
	
					if (lastword) { dot = true; }

					while (a <= i && b<=f) {


						ansfound[u] = grid[a][b];
						u++;
						gridc[a][b] = '.';
						numgrid[a][b]= numgrid[a][b]+1;

						b++;
						a++;
					}
				}



				fd = false;
				i++;
				f++;
			}


		}

	}
	i = 0;

	cout << wlcount;

	i = 0;

	while (i < u) {

		cout << ansfound[i] << " ";
		i++;
	}

	if (wordfound) {
		for (int i = 0;i < 15;i++) {

			for (int j = 0;j < 15;j++) {

				cout << setw(3) << gridc[i][j];

			}

			cout << endl;

		}
		return 1;
	}
	else {
		return 0;
	}

}

bool dlsearch(char grid[][15], char temp[], int wlcount, char gridc[][15], int numgrid[][15]) {

	int i = 0, z, k, a = 0, h = 0, f = 0, g = 0, d = 0, u = 0, hcount;
	int wfcount = 0, chk = 0;
	char ansfound[225];
	bool comma = false, wordfound = false, fd = false, firstMatch = true, dot = false;
	bool lastword = false;
	int p = 0;
	bool nSame = false;
	int b = 0;


	for (g = 0;g < 15;g++) {
		for (int m = 14;m >= 0;m--) {

			i = g;
			f = m;

			while (i < 15 && f >= 0) {


				int y = int(temp[d]);

				int x = int(grid[i][f] + 32);



				if (temp[d] == grid[i][f] || x == y)
				{


					if (firstMatch) {
						a = i;
						b = f;
					}

					firstMatch = false;
					fd = true;
					d++;
					wfcount++;

				}


				else if (temp[d] != grid[i][f] && !fd || x != y && !fd) {

					d = 0;

					wfcount = 0;
					firstMatch = true;

					int y = int(temp[d]);

					int x = int(grid[i][f] + 32);

					if (temp[d] == grid[i][f] || x == y) {
						d++;

						wfcount++;
						firstMatch = true;
						if (firstMatch) {
							a = i;
							b = f;
						}
						firstMatch = false;
					}
				}


				if (wfcount == wlcount) {
					h = h + 1;
					p = 0;
					wordfound = true;
					comma = false;
					if (lastword) { dot = true; }



					while (a <= i && b >= f) {


						ansfound[u] = grid[a][b];
						u++;
						gridc[a][b] = '.';
						numgrid[a][b]= numgrid[a][b]+1;
						b--;
						a++;
					}
				}

				fd = false;
				i++;
				f--;
			}



		}


	}

	i = 0;

	cout << wlcount;

	i = 0;

	while (i < u) {

		cout << ansfound[i] << " ";
		i++;
	}

	if (wordfound) {
		for (int i = 0;i < 15;i++) {

			for (int j = 0;j < 15;j++) {

				cout << setw(3) << gridc[i][j];

			}
			cout << endl;

		}




		return 1;
	}
	else {
		return 0;

	}

}

bool ursearch(char grid[][15], char temp[], int wlcount, char gridc[][15], int numgrid[][15]) {

	int i = 0, z, k, a = 0, h = 0, f = 0, g = 0, d = 0, u = 0, hcount;
	int wfcount = 0, chk = 0;
	char ansfound[225];
	bool comma = false, wordfound = false, fd = false, firstMatch = true, dot = false;
	bool lastword = false;
	int p = 0;
	bool nSame = false;
	int b = 0;
	



	for (g = 14;g >= 0;g--) {

		for (int m = 14;m >= 0;m--) {
			
			i = g;
			f = m;

			while (i >= 0 && f >= 0) {

				int y = int(temp[d]);

				int x = int(grid[i][f] + 32);

				if (temp[d] == grid[i][f] || x == y)
				{


					if (firstMatch) {
						a = i;
						b = f;
					}

					firstMatch = false;
					fd = true;
					d++;
					wfcount++;

				}


				else if (temp[d] != grid[i][f] && !fd || x != y && !fd) {

					d = 0;
					wfcount = 0;
					firstMatch = true;
					int y = int(temp[d]);
					int x = int(grid[i][f] + 32);

					if (temp[d] == grid[i][f] || x == y) {
						d++;
						wfcount++;
						firstMatch = true;




						if (firstMatch) {
							a = i;
							b = f;
						}
						firstMatch = false;
					}
				}


				if (wfcount == wlcount) {
					h = h + 1;
					p = 0;
					wordfound = true;
					comma = false;
					if (lastword) { dot = true; }



					while (a >= i && b >= f) {
						ansfound[u] = grid[a][b];
						u++;
						gridc[a][b] = '.';
						numgrid[a][b]= numgrid[a][b]+1;
						b--;
						a--;
					}
				}
				fd = false;
				i--;
				f--;
			}



		}
	}

	i = 0;
	cout << wlcount;

	i = 0;

	while (i < u) {

		cout << ansfound[i] << " ";
		i++;
	}

	if (wordfound) {
		
		for (int i = 0;i < 15;i++) {

			for (int j = 0;j < 15;j++) {

				cout << setw(3) << gridc[i][j];
			}
			cout << endl;

		}




		return 1;
	}
	else {
		return 0;
	}

}

bool ulsearch(char grid[][15], char temp[], int wlcount, char gridc[][15], int numgrid[][15]) {

	int i = 0, z, k, a = 0, h = 0, f = 0, g = 0, d = 0, u = 0, hcount;
	int  wfcount = 0, chk = 0;
	char ansfound[225];
	bool comma = false, wordfound = false, fd = false, firstMatch = true, dot = false;
	bool lastword = false;
	int p = 0;
	bool nSame = false;
	int b = 0;
	int m = 0;

	

	for (g = 14;g >= 0;g--) {
		m = 0;



		for (m = 0; m < 15;m++) {
			f = m;
			i = g;




			while (i >= 0 && f < 15) {
				int y = int(temp[d]);
				int x = int(grid[i][f] + 32);

				if (temp[d] == grid[i][f] || x == y)
				{
					if (firstMatch) {
						a = i;
						b = f;
					}

					firstMatch = false;
					fd = true;
					d++;
					wfcount++;
				}


				else if (temp[d] != grid[i][f] && !fd || x != y && !fd) {

					d = 0;
					wfcount = 0;
					firstMatch = true;
					int y = int(temp[d]);
					int x = int(grid[i][f] + 32);
					if (temp[d] == grid[i][f] || x == y) {
						d++;

						wfcount++;

						firstMatch = true;
						if (firstMatch) {
							a = i;
							b = f;
						}
						firstMatch = false;
					}
				}


				if (wfcount == wlcount) {
					h = h + 1;

					p = 0;

					wordfound = true;

					comma = false;

					if (lastword) { dot = true; }



					while (a >= i && b <= f) {


						ansfound[u] = grid[a][b];

						u++;

						gridc[a][b] = '.';
						numgrid[a][b]= numgrid[a][b]+1;
						a--;
						b++;
					}
				}
				fd = false;
				i--;
				f++;
			}

		}
		
	}

	i = 0;

	cout << wlcount;

	i = 0;

	while (i < u) {

		cout << ansfound[i] << " ";
		i++;
	}

	if (wordfound) {
		
		for (int i = 0;i < 15;i++) {

			for (int j = 0;j < 15;j++) {

				cout << setw(3) << gridc[i][j];

			}

			cout << endl;

		}

		return 1;
	}
	else {
		return 0;
	}

}

int grido(char grid[][15]) {

	int i = 0, j = 0;

	for (i = 0;i < 15;i++) {


		for (j = 0;j < 15;j++) {

			cout << setw(3) << grid[i][j];

		}
		cout << endl;

	}

	return 0;
}

void setcolor(int value) {
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),value);
 }



int central() {

	bool wordfound = true, comma = false, lastword = false, dot = false;
	char answ[2000], temp1[15], grid1[15][15], grid2[15][15];
	int p = 0, h=0, count=0;
	int wl1count=0;
	int choice;


	ansinput(answ);
	gridcopy(grid2);
	gridout(grid1);

	cout << "Which option would you like to select? 1 for Teleword at once:" << endl;
	cin >> choice;




	if (wordfound) {

		while (!comma) {

			if (answ[h] != ',') {

				temp1[p] = answ[h];

				p++;

				wl1count++;
				if (answ[h] != '.') {
					h++;
				}
			}

			else if (answ[h] == '.') { dot = true; comma = true; p = 0; }

			else { comma = true; p = 0; }

		}


	}

	wordfound = false;


	while (!lastword) {



		if (rhsearch(grid1, temp1, wl1count, grid2, num)) {
			if (dot) { count++; }
			h = h + 1;
			wl1count = 0;
			wordfound = true;
			comma = false;
			pnumgrid(num);

			if (wordfound && !dot) {

				while (!comma) {

					if (answ[h] != ',' && answ[h] != '.') {

						temp1[p] = answ[h];

						p++;

						wl1count++;
						if (answ[h] != '.') {
							h++;
						}
					}

					if (answ[h] == '.') { dot = true; comma = true; p = 0; }

					else if (answ[h] == ',') { comma = true; p = 0; }

				}


			}

			wordfound = false;
		}

		else if (upsearch(grid1, temp1, wl1count, grid2, num)) {
			if (dot) { count++; }
				h = h + 1;
				wl1count = 0;
				wordfound = true;
				comma = false;
				pnumgrid(num);


				if (wordfound && !dot) {

					while (!comma) {

						if (answ[h] != ',' && answ[h] != '.') {

							temp1[p] = answ[h];

							p++;

							wl1count++;
							if (answ[h] != '.') {
								h++;
							}
						}

						if (answ[h] == '.') { dot = true; comma = true; p = 0; }

						else if (answ[h] == ',') { comma = true; p = 0; }

					}


				}

				wordfound = false;
		}
		else if (dosearch(grid1, temp1, wl1count, grid2, num)) {
			if (dot) { count++; }
			h = h + 1;
			wl1count = 0;
			wordfound = true;
			comma = false;
			pnumgrid(num);


			if (wordfound && !dot) {

				while (!comma) {

					if (answ[h] != ',' && answ[h] != '.') {

						temp1[p] = answ[h];

						p++;

						wl1count++;
						if (answ[h] != '.') {
							h++;
						}
					}

					if (answ[h] == '.') { dot = true; comma = true; p = 0; }

					else if (answ[h] == ',') { comma = true; p = 0; }

				}


			}

			wordfound = false;
		}

		else if (lhsearch(grid1, temp1, wl1count, grid2, num)) {
		if (dot) { count++; }
		h = h + 1;
		wl1count = 0;
		wordfound = true;
		comma = false;
		pnumgrid(num);

		if (wordfound && !dot) {

			while (!comma) {

				if (answ[h] != ',' && answ[h] != '.') {

					temp1[p] = answ[h];

					p++;

					wl1count++;
					if (answ[h] != '.') {
						h++;
					}
				}

				if (answ[h] == '.') { dot = true; comma = true; p = 0; }

				else if (answ[h] == ','){ comma = true; p = 0; }

			}

		}

		wordfound = false;
		}

		else if (drsearch(grid1, temp1, wl1count, grid2, num)) {
		if (dot) { count++; }
		h = h + 1;
		wl1count = 0;
		wordfound = true;
		comma = false;
		pnumgrid(num);


		if (wordfound && !dot) {

			while (!comma) {

				if (answ[h] != ',' && answ[h] != '.') {

					temp1[p] = answ[h];

					p++;

					wl1count++;
					if (answ[h] != '.') {
						h++;
					}
				}

				if (answ[h] == '.') { dot = true; comma = true; p = 0; }

				else if (answ[h] == ',') { comma = true; p = 0; }

			}

		}

		wordfound = false;
		}

		else if (dlsearch(grid1, temp1, wl1count, grid2, num)) {
		if (dot) { count++; }
			h = h + 1;
			wl1count = 0;
			wordfound = true;
			comma = false;
			pnumgrid(num);


			if (wordfound && !dot) {

				while (!comma) {

					if (answ[h] != ',' && answ[h] != '.') {

						temp1[p] = answ[h];
						p++;
						wl1count++;
						if (answ[h] != '.') {
							h++;
						}
					}
					if (answ[h] == '.') { dot = true; comma = true; p = 0; }

					else if (answ[h] == ',') { comma = true; p = 0; }

				}

			}

			wordfound = false;
		}

		else if (ursearch(grid1, temp1, wl1count, grid2, num)) {
		if (dot) { count++; }
			h = h + 1;
			wl1count = 0;
			wordfound = true;
			comma = false;
			pnumgrid(num);

			if (wordfound && !dot) {

				while (!comma) {

					if (answ[h] != ',' && answ[h] != '.') {

						temp1[p] = answ[h];

						p++;

						wl1count++;
						if (answ[h] != '.') {
							h++;
						}
					}

					if (answ[h] == '.') { dot = true; comma = true; p = 0; }

					else if (answ[h] == ',') { comma = true; p = 0; }

				}

			}

			wordfound = false;
		}

		else if (ulsearch(grid1, temp1, wl1count, grid2, num)) {
		if (dot) { count++; }
		h = h + 1;
		wl1count = 0;
		wordfound = true;
		comma = false;
		pnumgrid(num);


		if (wordfound && !dot) {

			while (!comma) {

				if (answ[h] != ',' && answ[h] != '.') {

					temp1[p] = answ[h];

					p++;

					wl1count++;
					if (answ[h] != '.') {
						h++;
					}
				}

				if (answ[h] == '.') { dot = true; comma = true; p = 0; }

				else if (answ[h] == ',') { comma = true; p = 0; }

			}


		}

		wordfound = false;
		}
		if (dot && count==1) { lastword = true; }

	}

	cout << endl;
	for (int i=0;i<15;i++) {
	
		for (int j = 0;j < 15;j++) {

		cout << setw(3) << grid2[i][j];

	}
	cout << endl;

}

int	i = 0, j = 0;
	char teleword[100];
	int u = 0;

	for (i = 0;i < 15;i++) {

		for (j = 0;j < 15;j++)
		{
			if (grid2[i][j] != '.') {
				teleword[u] = grid2[i][j];
				u++;
			}

		}

	}

	j = 0;
	cout << endl;
	cout << "The teleword is: ";

	for (j = 0;j < u;j++) {
		cout << teleword[j];
	}
	cout << endl;
	return 0;
}









int main() {

	int num[15][15];

	central();
	

	system("pause");
	return 0;

}
