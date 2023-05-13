#include <vector>

class MultidimensionalArray {
private:
    std::vector<int> shape_; 
    std::vector<int> strides_; 
    std::vector<int> data_; 
public:
    MultidimensionalArray(const std::vector<int>& shape) {
        shape_ = shape;

        
        int stride = 1;
        for (int i = shape.size() - 1; i >= 0; i--) {
            strides_.insert(strides_.begin(), stride);
            stride *= shape[i];
        }

        
        data_.resize(stride);
    }

    
    int& operator()(const std::vector<int>& indices) {
        int index = 0;
        for (int i = 0; i < indices.size(); i++) {
            index += indices[i] * strides_[i];
        }
        return data_[index];
    }

    
    int& operator[](const std::vector<int>& indices) {
        std::vector<int> iliffe_indices;
        for (int i = 0; i < shape_.size(); i++) {
            int index = 0;
            int stride = strides_[i];
            for (int j = i; j < indices.size(); j++) {
                index += (indices[j] % shape_[j]) * stride;
                stride *= shape_[j];
            }
            iliffe_indices.push_back(index);
        }
        return data_[iliffe_index(iliffe_indices)];
    }

    
    std::vector<int> get_indices(int index) {
        std::vector<int> indices;
        for (int i = 0; i < shape_.size(); i++) {
            int stride = strides_[i];
            indices.push_back(index / stride);
            index %= stride;
        }
        return indices;
    }

private:
    int iliffe_index(const std::vector<int>& indices) {
        int index = 0;
        int stride = 1;
        for (int i = indices.size() - 1; i >= 0; i--) {
            index += indices[i] * stride;
            stride *= shape_[i];
        }
        return index;
    }
};
