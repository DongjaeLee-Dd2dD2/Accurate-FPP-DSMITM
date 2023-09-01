#include <bits/stdc++.h>
using namespace std;

// Variables for First Phase
// In Codes <=> In Paper
// xx, yy, zz, ww <=> x', y', z', w'
// x[i][j] <=> x_i[j]
int x[6][16], y[6][16], z[6][16], w[6][16], xx[6][16], yy[6][16], zz[6][16], ww[6][16], dx[6][16], dy[6][16], dz[6][16], dw[6][16];

// Variables for Second Phase
// In Codes <=> In Paper
// X[i][j] <=> X_1^i[j], X_2^i[j], X_3^i[j], X_4^i[j] (We reuse the variable X[i][j])
// DX <=> Delta X
int X[256][16], Y[256][16], Z[256][16], W[256][16], DX[256][16], DY[256][16], DZ[256][16], DW[256][16];

// S-box, Inverse S-box
int Sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
int iSbox[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

// Differential Distribution Table
vector<int> DDT[256][256];

// For File Output
FILE* in;

// For counting gathered sequences
int seq_cnt = 0;
int sampling_threshold = 1 << 20;

// Multiplication on GF(2^8)
int MUL(int a, int b);

// Construct DDT
void build_DDT();

// Step 1. of First Phase.
void get_10_params();

// Step 2. of First Phase + Second Phase
void get_24_params();

// Second Phase.
void get_sequence();

// main
int main() {
	in = fopen("Sampling_Result_AES.txt", "w");
	build_DDT();
	while (true) {
		get_10_params(); // Step 1. of First Phase
		get_24_params(); // Step 2. of First Phase + Second Phase
		if (seq_cnt == sampling_threshold) {
			fclose(in);
			break;
		}
	}
}

// Multiplication on GF(2^8)
int MUL(int a, int b) {
	int ret = 0;
	for (int i = 0; i < 8; i++) {
		if ((b >> i) & 1) ret ^= (a << i);
	}
	for (int i = 14; i >= 8; i--) {
		if ((ret >> i) & 1) ret ^= (0x11b << (i - 8));
	}

	return ret;
}

// Construct DDT
void build_DDT() {
	for (int i = 0; i < 256; i++) {
		for (int j = i + 1; j < 256; j++) {
			DDT[i ^ j][Sbox[i] ^ Sbox[j]].push_back(i);
			DDT[i ^ j][Sbox[i] ^ Sbox[j]].push_back(j);
		}
	}
}

// Step 1. of First Phase.
void get_10_params() {
	dz[1][0] = rand() % 255 + 1;
	x[2][0] = rand() % 256;
	x[2][1] = rand() % 256;
	x[2][2] = rand() % 256;
	x[2][3] = rand() % 256;
	dw[4][0] = rand() % 255 + 1;
	z[4][0] = rand() % 256;
	z[4][1] = rand() % 256;
	z[4][2] = rand() % 256;
	z[4][3] = rand() % 256;
}

// Step 2. of First Phase + Second Phase
void get_24_params() {
	// Step 2-(a). of First Phase.
	// dz[1][0] -> dx[2][0,1,2,3] 
	dx[2][0] = MUL(dz[1][0], 0x02);
	dx[2][1] = dz[1][0];
	dx[2][2] = dz[1][0];
	dx[2][3] = MUL(dz[1][0], 0x03);

	// Step 2-(b). of First Phase.
	// x[2][0,1,2,3], dx[2][0,1,2,3] -> x'[2][0,1,2,3]
	xx[2][0] = x[2][0] ^ dx[2][0];
	xx[2][1] = x[2][1] ^ dx[2][1];
	xx[2][2] = x[2][2] ^ dx[2][2];
	xx[2][3] = x[2][3] ^ dx[2][3];

	// x[2][0,1,2,3], x'[0,1,2,3] -> dz[2][0,7,10,13]
	for (int i = 0; i < 4; i++) y[2][i] = Sbox[x[2][i]];
	for (int i = 0; i < 4; i++) yy[2][i] = Sbox[xx[2][i]];
	for (int i = 0; i < 4; i++) dy[2][i] = y[2][i] ^ yy[2][i];

	dz[2][0] = dy[2][0];
	dz[2][13] = dy[2][1];
	dz[2][10] = dy[2][2];
	dz[2][7] = dy[2][3];

	// dz[2][0,7,10,13] -> dx[3]
	dx[3][0] = MUL(dz[2][0], 0x02);
	dx[3][1] = dz[2][0];
	dx[3][2] = dz[2][0];
	dx[3][3] = MUL(dz[2][0], 0x03);

	dx[3][4] = dz[2][7];
	dx[3][5] = dz[2][7];
	dx[3][6] = MUL(dz[2][7], 0x03);
	dx[3][7] = MUL(dz[2][7], 0x02);

	dx[3][8] = dz[2][10];
	dx[3][9] = MUL(dz[2][10], 0x03);
	dx[3][10] = MUL(dz[2][10], 0x02);
	dx[3][11] = dz[2][0];

	dx[3][12] = MUL(dz[2][13], 0x03);
	dx[3][13] = MUL(dz[2][13], 0x02);
	dx[3][14] = dz[2][13];
	dx[3][15] = dz[2][13];

	// Steo 2-(c). of First Phase.
	// dw[4][0] -> dz[4][0,1,2,3]
	dz[4][0] = MUL(dw[4][0], 0x0e);
	dz[4][1] = MUL(dw[4][0], 0x09);
	dz[4][2] = MUL(dw[4][0], 0x0d);
	dz[4][3] = MUL(dw[4][0], 0x0b);

	// z[4][0,1,2,3], dz[4][0,1,2,3] -> x[4][0,5,10,15], x'[4][0,5,10,15]
	for (int i = 0; i < 4; i++) zz[4][i] = z[4][i] ^ dz[4][i];

	y[4][0] = z[4][0];
	y[4][5] = z[4][1];
	y[4][10] = z[4][2];
	y[4][15] = z[4][3];
	yy[4][0] = zz[4][0];
	yy[4][5] = zz[4][1];
	yy[4][10] = zz[4][2];
	yy[4][15] = zz[4][3];

	for (int i = 0; i < 4; i++) x[4][i * 5] = iSbox[y[4][i * 5]];
	for (int i = 0; i < 4; i++) xx[4][i * 5] = iSbox[yy[4][i * 5]];

	// Step 2-(d). of First Phase.
	// x[4][0,5,10,15], x'[4][0,5,10,15] -> dx[4][0,5,10,15]
	for (int i = 0; i < 4; i++) dx[4][i * 5] = x[4][i * 5] ^ xx[4][i * 5];

	// dx[4][0,5,10,15] -> dy[3]
	for (int i = 0; i < 4; i++) dw[3][i * 5] = dx[4][i * 5];

	dz[3][0] = MUL(dw[3][0], 0x0e);
	dz[3][1] = MUL(dw[3][0], 0x09);
	dz[3][2] = MUL(dw[3][0], 0x0d);
	dz[3][3] = MUL(dw[3][0], 0x0b);

	dz[3][4] = MUL(dw[3][5], 0x0b);
	dz[3][5] = MUL(dw[3][5], 0x0e);
	dz[3][6] = MUL(dw[3][5], 0x09);
	dz[3][7] = MUL(dw[3][5], 0x0d);

	dz[3][8] = MUL(dw[3][10], 0x0d);
	dz[3][9] = MUL(dw[3][10], 0x0b);
	dz[3][10] = MUL(dw[3][10], 0x0d);
	dz[3][11] = MUL(dw[3][10], 0x09);

	dz[3][12] = MUL(dw[3][15], 0x09);
	dz[3][13] = MUL(dw[3][15], 0x0d);
	dz[3][14] = MUL(dw[3][15], 0x0b);
	dz[3][15] = MUL(dw[3][15], 0x0e);

	for (int i = 0; i < 16; i++) dy[3][i] = dz[3][(16 + i - (i % 4) * 5) % 16];

	// Step 2-(e). of First Phase.
	// Solve 16 S-box differential equations between DX[3] and DY[3]

	// No solution is found
	for (int i = 0; i < 16; i++) {
		if (DDT[dx[3][i]][dy[3][i]].size() == 0) return;
	}

	// Solutions are found
	for (auto i0 : DDT[dx[3][0]][dy[3][0]]) {
		for (auto i1 : DDT[dx[3][1]][dy[3][1]]) {
			for (auto i2 : DDT[dx[3][2]][dy[3][2]]) {
				for (auto i3 : DDT[dx[3][3]][dy[3][3]]) {
					for (auto i4 : DDT[dx[3][4]][dy[3][4]]) {
						for (auto i5 : DDT[dx[3][5]][dy[3][5]]) {
							for (auto i6 : DDT[dx[3][6]][dy[3][6]]) {
								for (auto i7 : DDT[dx[3][7]][dy[3][7]]) {
									for (auto i8 : DDT[dx[3][8]][dy[3][8]]) {
										for (auto i9 : DDT[dx[3][9]][dy[3][9]]) {
											for (auto i10 : DDT[dx[3][10]][dy[3][10]]) {
												for (auto i11 : DDT[dx[3][11]][dy[3][11]]) {
													for (auto i12 : DDT[dx[3][12]][dy[3][12]]) {
														for (auto i13 : DDT[dx[3][13]][dy[3][13]]) {
															for (auto i14 : DDT[dx[3][14]][dy[3][14]]) {
																for (auto i15 : DDT[dx[3][15]][dy[3][15]]) {
																	x[3][0] = i0;
																	x[3][1] = i1;
																	x[3][2] = i2;
																	x[3][3] = i3;
																	x[3][4] = i4;
																	x[3][5] = i5;
																	x[3][6] = i6;
																	x[3][7] = i7;
																	x[3][8] = i8;
																	x[3][9] = i9;
																	x[3][10] = i10;
																	x[3][11] = i11;
																	x[3][12] = i12;
																	x[3][13] = i13;
																	x[3][14] = i14;
																	x[3][15] = i15;

																	// Prceed to the Second Phase with each solution
																	get_sequence(); // <- Second Phase
																	if (seq_cnt == sampling_threshold) return;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

// Second Phase.
void get_sequence() {
	for (int i = 0; i < 256; i++) {
		// Step 1-(a). of Second Phase.
		// Assign i to DZ_1^i[0]
		DZ[i][0] = i;

		// DZ_1^i[0] -> DX_2^i[0,1,2,3]
		DX[i][0] = MUL(DZ[i][0], 0x02);
		DX[i][1] = MUL(DZ[i][0], 0x03);
		DX[i][2] = DZ[i][0];
		DX[i][3] = DZ[i][0];

		// Step 1-(b). of Second Phase.
		// X_2^0[0,1,2,3], DX_2^i[0,1,2,3] -> X_2^i[0,1,2,3]
		X[i][0] = x[2][0] ^ DX[i][0];
		X[i][1] = x[2][1] ^ DX[i][1];
		X[i][2] = x[2][2] ^ DX[i][2];
		X[i][3] = x[2][3] ^ DX[i][3];

		// X_2^i[0,1,2,3] -> Z_2^i[0,7,10,13]
		Z[i][0] = Sbox[X[i][0]];
		Z[i][13] = Sbox[X[i][1]];
		Z[i][10] = Sbox[X[i][2]];
		Z[i][7] = Sbox[X[i][3]];

		// Step 1-(c). of Second Phase.
		// Z_2^0[0,7,10,13], Z_2^i[0,7,10,13] -> DZ_2^i[0,7,10,13]
		DZ[i][0] = Z[0][0] ^ Z[i][0];
		DZ[i][13] = Z[0][13] ^ Z[i][13];
		DZ[i][10] = Z[0][10] ^ Z[i][10];
		DZ[i][7] = Z[0][7] ^ Z[i][7];

		// DZ_2^i[0,7,10,13] -> DX_3^i
		DX[i][0] = MUL(DZ[i][0], 0x02);
		DX[i][1] = DZ[i][0];
		DX[i][2] = DZ[i][0];
		DX[i][3] = MUL(DZ[i][0], 0x03);

		DX[i][4] = DZ[i][7];
		DX[i][5] = DZ[i][7];
		DX[i][6] = MUL(DZ[i][7], 0x03);
		DX[i][7] = MUL(DZ[i][7], 0x02);

		DX[i][8] = DZ[i][10];
		DX[i][9] = MUL(DZ[i][10], 0x03);
		DX[i][10] = MUL(DZ[i][10], 0x02);
		DX[i][11] = DZ[i][10];

		DX[i][12] = MUL(DZ[i][13], 0x03);
		DX[i][13] = MUL(DZ[i][13], 0x02);
		DX[i][14] = DZ[i][13];
		DX[i][15] = DZ[i][13];

		// Step 1-(d). of Second Phase.
		// X_3^0, DX_3^i -> X_3^i
		for (int j = 0; j < 16; j++) X[i][j] = x[3][j] ^ DX[i][j];

		// X_3^i -> Z_3^i
		for (int j = 0; j < 16; j++) Z[i][j] = Sbox[X[i][(j + (j % 4) * 4) % 16]];

		// Step 1-(e). of Second Phase.
		// Z_3^0, Z_3^i -> DZ_3^i
		for (int j = 0; j < 16; j++) DZ[i][j] = Z[0][j] ^ Z[i][j];

		// DZ_3^i -> DX_4^i[0,5,10,15]
		DX[i][0] = MUL(DZ[i][0], 0x02) ^ MUL(DZ[i][1], 0x03) ^ DZ[i][2] ^ DZ[i][3];
		DX[i][5] = DZ[i][4] ^ MUL(DZ[i][5], 0x02) ^ MUL(DZ[i][6], 0x03) ^ DZ[i][7];
		DX[i][10] = DZ[i][8] ^ DZ[i][9] ^ MUL(DZ[i][10], 0x02) ^ MUL(DZ[i][11], 0x03);
		DX[i][15] = MUL(DZ[i][12], 0x03) ^ DZ[i][13] ^ DZ[i][14] ^ MUL(DZ[i][15], 0x02);

		// Step 1-(f). of Second Phase.
		// X_4^0[0,5,10,15], DX_4^i[0,5,10,15] -> X_4^i[0,5,10,15]
		X[i][0] = x[4][0] ^ DX[i][0];
		X[i][5] = x[4][5] ^ DX[i][5];
		X[i][10] = x[4][10] ^ DX[i][10];
		X[i][15] = x[4][15] ^ DX[i][15];

		// X_4^i[0,5,10,15] -> Z_4^i[0,1,2,3]
		Z[i][0] = Sbox[X[i][0]];
		Z[i][1] = Sbox[X[i][5]];
		Z[i][2] = Sbox[X[i][10]];
		Z[i][3] = Sbox[X[i][15]];

		// Step 1-(g). of Second Phase.
		// Z_4^0[0,1,2,3], Z_4^i[0,1,2,3] -> DZ_4^i[0,1,2,3]
		DZ[i][0] = Z[0][0] ^ Z[i][0];
		DZ[i][1] = Z[0][1] ^ Z[i][1];
		DZ[i][2] = Z[0][2] ^ Z[i][2];
		DZ[i][3] = Z[0][3] ^ Z[i][3];

		// DZ_4^i[0,1,2,3] -> C^i[0]
		DW[i][0] = MUL(DZ[i][0], 0x02) ^ MUL(DZ[i][1], 0x03) ^ DZ[i][2] ^ DZ[i][3];

		// Step 2. of Second Phase.
		fprintf(in, "%d ", DW[i][0]);
	}
	fprintf(in, "\n");
	seq_cnt++;
}
