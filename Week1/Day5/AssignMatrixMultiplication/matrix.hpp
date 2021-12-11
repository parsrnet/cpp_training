class Matrix
{
private:
	int** matrix;
	unsigned height, width;
public:
	Matrix(int h, int w, int** arr) : height(h), width(w)
	{
		matrix = new int*[height];
		for (unsigned row = 0; row < height; row++)
		{
			matrix[row] = new int[width];
			//memcpy(matrix[row], arr[row], sizeof(int) * width); // Why is this causing memory leaks?
			for (unsigned col = 0; col < width; col++)
				matrix[row][col] = arr[row][col];
		}
		memcpy(&matrix, &arr, sizeof(int) * height * width);
	}
	template<size_t Rows, size_t Cols, typename T = int>
	Matrix(const T (&arr)[Rows][Cols]) : height(Rows), width(Cols)
	{
		matrix = new int* [height];
		for (unsigned row = 0; row < Rows; row++)
		{
			matrix[row] = new int[width];
			//memcpy(matrix[row], arr[row], sizeof(int) * Cols); // Why is this causing memory leaks?
			for (unsigned col=0; col < Cols; col++)
				matrix[row][col] = arr[row][col];
		}
	}

	~Matrix()
	{
	}

	int at(unsigned row, unsigned col) const
	{
		if (row >= 0 && row < height 
			&& col >= 0 && col < width)
			return matrix[row][col];
		else
			return 0;
	}
	
	size_t size(int i) const
	{
		if (i == 0)
			return height;
		else if (i == 1)
			return width;
		else
			return 0;
	}

	void print()
	{
		std::cout << "[" << std::endl;
		for (unsigned row = 0; row < height; row++)
		{
			std::cout << "\t[ ";
			for (unsigned col = 0; col < width-1; col++)
				std::cout << matrix[row][col] << ", ";
			std::cout << matrix[row][width-1] << " ]" << std::endl;
		}
		std::cout << "]" << std::endl;
	}

	static Matrix dot_product(const Matrix& matrix1, const Matrix& matrix2)
	{
		assert(matrix1.size(0) == matrix2.size(1));
		int** dotProduct = new int*[matrix1.size(0)];

		for (unsigned row = 0; row < matrix1.size(0); row++)
		{
			dotProduct[row] = new int[matrix2.size(1)];
			for (unsigned col = 0; col < matrix2.size(1); col++)
			{
				int product = 0;
				for (unsigned i = 0; i < matrix1.size(1); i++)
					product += matrix1.at(row, i) * matrix2.at(i, col);
				dotProduct[row][col] = product;
			}
		}
		return Matrix(matrix1.size(0), matrix2.size(1), dotProduct);
	}
};
