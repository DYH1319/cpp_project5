#pragma once

#include <iostream>

using namespace std;

template<typename T>
class Matrix {
private:
    size_t rows;
    size_t cols;
    size_t channels;
    int *count;
    T *data;
public:
    Matrix(size_t rows, size_t cols, size_t channels) : rows(rows), cols(cols), channels(channels) {
        data = new T[rows * cols * channels * sizeof(T)]{};
        count = new int[1]{1};
    }

    Matrix(size_t rows, size_t cols, size_t channels, T *data) : rows(rows), cols(cols), channels(channels), data(data) {
        count = new int[1]{1};
    }

    ~Matrix() {
        if (*count == 1) {
            delete[] data;
            delete[] count;
            cerr << "delete()" << endl;
        } else {
            (*count)--;
        }
    }

    Matrix(const Matrix<T> & matrix) : rows(matrix.rows), cols(matrix.cols), channels(matrix.channels), count(matrix.count), data(matrix.data) {
        (*count)++;
    }

    bool setElement(size_t row, size_t col, size_t channel, T value) {
        if (row >= this->rows || col >= this->cols || channel >= this->channels) {
            cerr << "setElement(): Indices are out of range" << endl;
            return false;
        }
        data[row * this->cols * this->channels + col * this->channels + channel] = value;
        return true;
    }

    void print() {
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                for (size_t k = 0; k < this->channels; k++) {
                    if (k != this->channels - 1) {
                        cout << this->data[i * (this->cols) * (this->channels) + j * (this->channels) + k] << ",";
                    } else {
                        cout << this->data[i * (this->cols) * (this->channels) + j * (this->channels) + k] << "  ";
                    }
                }
            }
            cout << endl;
        }
    }

    Matrix<T> &operator=(const Matrix<T> &matrix) {
        if (&matrix != this) {
            this->rows = matrix.rows;
            this->cols = matrix.cols;
            this->channels = matrix.channels;
            this->data = matrix.data;
            this->count = matrix.count;
            (*count)++;
        }
        return *this;
    }

    bool operator==(const Matrix<T> &matrix) const {
        if (this->rows != matrix.rows || this->cols != matrix.cols || this->channels != matrix.channels) {
            return false;
        }
        for (size_t i = 0; i < rows * cols * channels; i++) {
            if (this->data[i] != matrix.data[i]) {
                return false;
            }
        }
        return true;
    }

    Matrix<T> operator+(const Matrix<T> &matrix) const {
        Matrix<T> res(rows, cols, channels);
        if (this->rows != matrix.rows || this->cols != matrix.cols || this->channels != channels) {
            cerr << "operator+(): Can't add these two matrix" << endl;
            return res;
        }
        for (size_t i = 0; i < rows * cols * channels; i++) {
            res.data[i] = this->data[i] + matrix.data[i];
        }
        return res;
    }

    Matrix<T> operator-(const Matrix<T> &matrix) const {
        Matrix<T> res(rows, cols, channels);
        if (this->rows != matrix.rows || this->cols != matrix.cols || this->channels != channels) {
            cerr << "operator-(): Can't minus these two matrix" << endl;
            return res;
        }
        for (size_t i = 0; i < rows * cols * channels; i++) {
            res.data[i] = this->data[i] - matrix.data[i];
        }
        return res;
    }

    Matrix<T> &operator+=(const Matrix<T> &matrix) {
        if (this->rows != matrix.rows || this->cols != matrix.cols || this->channels != channels) {
            cerr << "operator+=(): Can't add these two matrix" << endl;
            return *this;
        }
        for (size_t i = 0; i < rows * cols * channels; i++) {
            this->data[i] += matrix.data[i];
        }
        return *this;
    }

    Matrix<T> &operator-=(const Matrix<T> &matrix) {
        if (this->rows != matrix.rows || this->cols != matrix.cols || this->channels != channels) {
            cerr << "operator-=(): Can't minus these two matrix" << endl;
            return *this;
        }
        for (size_t i = 0; i < rows * cols * channels; i++) {
            this->data[i] -= matrix.data[i];
        }
        return *this;
    }

    Matrix<T> operator*(const Matrix<T> &matrix) const {
        size_t row = this->rows;
        size_t col = matrix.cols;
        size_t channel = this->channels;

        Matrix<T> res(row, col, channel);
        if (this->cols != matrix.rows || this->channels != matrix.channels) {
            cerr << "operator*(): Can't multiply these two matrix" << endl;
            return res;
        }

        for (size_t i = 0; i < row; i++) {
            for (size_t j = 0; j < col; j++) {
                for (size_t k = 0; k < this->cols; k++) {
                    for (size_t l = 0; l < channel; l++) {
                        res.data[i * col * channel + j * channel + l] += this->data[i * this->cols * channel + k * channel + l] * matrix.data[k * col * channel + j * channel + l];
                    }
                }
            }
        }
        return res;
    }

    Matrix<T> operator+(T value) const {
        Matrix<T> res(rows, cols, channels);
        for (size_t i = 0; i < rows * cols * channels; i++) {
            res.data[i] = this->data[i] + value;
        }
        return res;
    }

    Matrix<T> &operator+=(T value) {
        for (size_t i = 0; i < rows * cols * channels; i++) {
            this->data[i] = this->data[i] + value;
        }
        return *this;
    }

    Matrix<T> operator-(T value) const {
        Matrix<T> res(rows, cols, channels);
        for (size_t i = 0; i < rows * cols * channels; i++) {
            res.data[i] = this->data[i] - value;
        }
        return res;
    }

    Matrix<T> &operator-=(T value) {
        for (size_t i = 0; i < rows * cols * channels; i++) {
            this->data[i] = this->data[i] - value;
        }
        return *this;
    }

    Matrix<T> operator*(T value) const {
        Matrix<T> res(rows, cols, channels);
        for (size_t i = 0; i < rows * cols * channels; i++) {
            res.data[i] = this->data[i] * value;
        }
        return res;
    }

    Matrix<T> &operator*=(T value) {
        for (size_t i = 0; i < rows * cols * channels; i++) {
            this->data[i] = this->data[i] * value;
        }
        return *this;
    }

    template<typename Y>
    friend ostream & operator<<(ostream & os, const Matrix<Y> &matrix);
};

template<typename Y>
ostream & operator<<(ostream & os, const Matrix<Y> &matrix) {
    for (size_t i = 0; i < matrix.rows; i++) {
        for (size_t j = 0; j < matrix.cols; j++) {
            for (size_t k = 0; k < matrix.channels; k++) {
                if (k != matrix.channels - 1) {
                    os << matrix.data[i * (matrix.cols) * (matrix.channels) + j * (matrix.channels) + k] << ",";
                } else {
                    os << matrix.data[i * (matrix.cols) * (matrix.channels) + j * (matrix.channels) + k] << "  ";
                }
            }
        }
        os << endl;
    }
    return os;
}
