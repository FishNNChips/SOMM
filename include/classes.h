#pragma once

template <typename T>
    requires std::floating_point<T>
class SOM
{
public:
    std::vector<std::vector<T>> &Data;
    std::vector<std::vector<T>> &W;
    T alpha = 0.5;

    SOM(std::vector<std::vector<T>> &Data, std::vector<std::vector<T>> &W) : Data(Data), W(W) {}
    SOM(std::vector<std::vector<T>> &Data, std::vector<std::vector<T>> &W, T alpha) : Data(Data), W(W), alpha(alpha) {}
    SOM(SOM<T> &Model) : Data(Model.Data), W(Model.W) {}

    void fit_transform(size_t epochs = 1)
    {
        Time t(__func__);
        STDerr.emplace_back(std::format("Function {}.{}() :- Epochs = {}\n", typeid(*this).name(), __func__, epochs));

        for (size_t i = 1; i <= epochs; ++i)
        {
            // F.emplace_back(format("{:*^50}\n", format("Epoch no.{}", i)));
            for (size_t j = 0, Jprev = -1, J = 0; j < Data.size(); ++j, Jprev = J)
            {
                // F.emplace_back(format("{:^50}\n", format("Datapoint[{}]", j)));
                J = winner(Data[j]);
                // F.emplace_back(format("INDEX = {}\n", J));
                update(Data[j], J);
            }
            // F.emplace_back("\n");
            alpha *= 0.5;
        }
    }
    size_t winner(std::vector<T> &sample)
    {
        // memset(&Distance[0], 0, Distance.size() * sizeof(T));
        float min = std::numeric_limits<float>::max();
        size_t J = 0;
#pragma omp parallel num_threads(8) // Change thread value accordingly
        {
            float temp = 0;
            float local_min = std::numeric_limits<float>::max();
            size_t local_J = 0;
#pragma omp for nowait
            for (int i = 0; i < W.size(); i++)
            {
                for (int j = 0; j < W[0].size(); j++)
                {
                    temp += (sample[j] - W[i][j]) * (sample[j] - W[i][j]);
                }
                (min < temp) ?: (min = temp, J = i);
                temp = 0;
            }
#pragma omp critical
            {
                if (local_min < min)
                    min = local_min, J = local_J;
                else if (min == local_min && J > local_J)
                    J = local_J;
                // F.emplace_back(format("(Dmin)^2 = {}, J = {}\n", min, J));
            }
        }
        return J;
    }
    void update(std::vector<T> &sample, size_t J)
    {
#pragma omp parallel for num_threads(8) // Change thread value accordingly
        for (int i = 0; i < W[0].size(); i++)
            W[J][i] += alpha * (sample[i] - W[J][i]);
    }
};
template <typename T>
    requires std::floating_point<T>
class SOMM : public SOM<T>
{
public:
    std::vector<std::vector<T>> &Wmap;
    SOMM() = delete;
    SOMM(std::vector<std::vector<T>> &Data, std::vector<std::vector<T>> &W, std::vector<std::vector<T>> Wmap) : SOM<T>(Data, W), Wmap(Wmap) {}
    void fit_transform(size_t epochs = 3)
    {
        Time t(__func__);
        STDerr.emplace_back(std::format("Function {}.{}() :- Epochs = {}\n", typeid(*this).name(), __func__, epochs));
        SOM<T>::fit_transform(epochs);
    }
};