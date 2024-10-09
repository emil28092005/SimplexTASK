#include <iostream>
#include <functional>
#include "tools/matrix.h"
#include "tools/math.h"
#include "simplex.h"

void _printInitialInputs(Vector &C, Matrix &A, Vector &b, double eps, bool maximize)
{
    std::cout << "Running for the following inputs:" << std::endl
              << std::endl;
    std::cout << "epsilon: " << eps << std::endl;
    if (maximize)
    {
        std::cout << "Maximize" << std::endl;
    }
    else
    {
        std::cout << "Minimize" << std::endl;
    }
    std::cout << "z = ";
    for (int i = 0; i < C.size(); i++)
    {
        bool isNegative = false;
        if (i != 0)
        {
            std::cout << " + ";
        }
        if (C[i] != 1)
        {
            if (C[i] < 0)
            {
                isNegative = true;
                std::cout << "(";
            }
            std::cout << C[i] << " * ";
        }

        std::cout << "x" << i + 1;
        if (isNegative)
        {
            std::cout << ")";
        }
    }
    std::cout << std::endl
              << "subject to the constrains:" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < A.getColumns(); j++)
        {
            bool isNegative = false;

            if (j != 0)
            {
                std::cout << " + ";
            }
            if (A[i][j] != 1)
            {
                if (A[i][j] < 0)
                {
                    isNegative = true;
                    std::cout << "(";
                }
                std::cout << A[i][j] << " * ";
            }
            std::cout << "x" << j + 1;
            if (isNegative)
            {
                std::cout << ")";
            }
        }
        std::cout << " <= " << b[i] << std::endl;
    }
}

int printResult(Result result)
{

    if (result.state == unsolvable)
    {
        std::cout << "The method is not applicable!" << std::endl;
    }
    else
    {
        std::cout << "SOLVED!" << std::endl;
        std::cout << "Decision variables: [";
        for (int i = 0; i < result.solution.size(); i++)
        {
            std::cout << result.solution[i];
            if (i != result.solution.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        std::cout << std::endl;
        if (result.maximize)
        {
            std::cout << "Maximum ";
        }
        else
        {
            std::cout << "Minimum ";
        }
        std::cout << "objective function value: " << result.objective_function_value << std::endl;
    }

    return 0;
}

bool check_eq(double a, double b, double relativeEpsilon = 0.0001)
{
    double diff = std::abs(a - b);
    a = std::abs(a);
    b = std::abs(b);
    double largest = (b > a) ? b : a;

    return diff <= largest * relativeEpsilon;
}

int TEST_GENERAL_CASE()
{
    std::cout << "----------------------------RUNNING_TEST_GENERAL_CASE----------------------------" << std::endl;

    Vector C = {5, 4};
    Matrix A = {
        {6, 4},
        {1, 2},
        {-1, 1},
        {0, 1}};
    Vector b = {24, 6, 1, 2};
    _printInitialInputs(C, A, b, 0.01, true);

    auto result = simplex(C, A, b);

    if (!(result.state == bounded))
    {
        std::string state_name;
        switch (result.state)
        {
        case unsolvable:
            state_name = "unsolvable";
            break;
        case unbounded:
            state_name = "unbounded";
            break;
        default:
            state_name = "bounded";
            break;
        }
        std::cout << "Incorrect state type. Expected bounded. Got " << state_name << std::endl;
        return 0;
    }

    if (!check_eq(result.objective_function_value, 21))
    {
        std::cout << "Incorrect objective function value. Expected 21. Got " // ЭТО УДАЛИТЬ?
                  << result.objective_function_value << std::endl;
        return 0;
    }

    if (!(check_eq(result.solution[0], 3) && check_eq(result.solution[1], 1.5)))
    {
        std::cout << "Incorrect desire variables. Expected 3 and 1.5. Got " // ЭТО УДАЛИТЬ?
                  << result.solution;
        return 0;
    }

    printResult(result);

    return 1;
}

int TEST_MINIMIZE_CASE()
{
    std::cout << "----------------------------RUNNING_TEST_MINIMIZE_CASE----------------------------" << std::endl;

    Vector C = {-2, 2, -6};
    Matrix A = {
        {2, 1, -2},
        {1, 2, 4},
        {1, -1, 2}};
    Vector b = {24, 23, 10};
    _printInitialInputs(C, A, b, 0.01, false);

    auto result = simplex(C, A, b, 0.01, false);

    if (!(result.state == bounded))
    {
        std::string state_name;
        switch (result.state)
        {
        case unsolvable:
            state_name = "unsolvable";
            break;
        case unbounded:
            state_name = "unbounded";
            break;
        default:
            state_name = "bounded";
            break;
        }
        std::cout << "Incorrect state type. Expected bounded. Got " << state_name << std::endl;
        return 0;
    }

    if (!check_eq(result.objective_function_value, -30.75))
    {
        std::cout << "Incorrect objective function value. Expected -30.75. Got "
                  << result.objective_function_value << std::endl;
        return 0;
    }

    if (!(check_eq(result.solution[0], 0) && check_eq(result.solution[1], 0.75) && check_eq(result.solution[2], 5.375)))
    {
        std::cout << "Incorrect desire variables. Expected 3 and 1.5. Got "
                  << result.solution;
        return 0;
    }

    printResult(result);

    return 1;
}

int TEST_WITH_SLACK_CASE()
{
    std::cout << "----------------------------RUNNING_TEST_WITH_SLACK_CASE----------------------------" << std::endl;

    Vector C = {2, -1, 0, -1};
    Matrix A = {
        {1, -2, 1, 0},
        {-2, -1, 0, -2},
        {3, 2, 0, 1}};
    Vector b = {10, 18, 36};

    _printInitialInputs(C, A, b, 0.01, true);

    auto result = simplex(C, A, b);

    if (!(result.state == bounded))
    {
        std::string state_name;
        switch (result.state)
        {
        case unsolvable:
            state_name = "unsolvable";
            break;
        case unbounded:
            state_name = "unbounded";
            break;
        default:
            state_name = "bounded";
            break;
        }
        std::cout << "Incorrect state type. Expected bounded. Got " << state_name << std::endl;
        return 0;
    }

    if (result.objective_function_value != 22.25)
    {
        std::cout << "Incorrect objective function value. Expected 22.25. Got "
                  << result.objective_function_value << std::endl;
        return 0;
    }

    if (!((result.solution[0] == 11.5) || (result.solution[1] == 0.75) ||
          (result.solution[2] == 0) || (result.solution[3] == 0)))
    {
        std::cout << "Incorrect desire variables. Expected 11.5, 0.75, 0, and 0. Got "
                  << result.solution;
        return 0;
    }

    printResult(result);

    return 1;
}

int TEST_UNBOUNDED_CASE()
{
    std::cout << "----------------------------RUNNING_TEST_UNBOUNDED_CASE----------------------------" << std::endl;

    Vector C = {2, 1};
    Matrix A = {
        {1, -1},
        {2, 0}};
    Vector b = {10, 40};

    _printInitialInputs(C, A, b, 0.01, true);

    auto result = simplex(C, A, b);

    if (!(result.state == unbounded))
    {
        std::string state_name;
        switch (result.state)
        {
        case unsolvable:
            state_name = "unsolvable";
            break;
        case unbounded:
            state_name = "unbounded";
            break;
        default:
            state_name = "bounded";
            break;
        }
        std::cout << "Incorrect state type. Expected unbounded. Got " << state_name << std::endl;
        return 0;
    }

    printResult(result);

    return 1;
}

int TEST_UNSOLVABLE_CASE()
{
    std::cout << "----------------------------RUNNING_TEST_UNSOLVABLE_CASE----------------------------" << std::endl;

    Vector C = {5, 4, 0, -5, 13};
    Matrix A = {
        {6, 4, 1, 3, 4},
        {1, 2, 0, 0, 2},
        {-1, 0, 0, 10, 0},
        {0, 1, 1, -5, 1}};
    Vector b = {-24, 6, 1, 2};

    _printInitialInputs(C, A, b, 0.01, true);

    auto result = simplex(C, A, b);

    if (!(result.state == unsolvable))
    {
        std::string state_name;
        switch (result.state)
        {
        case unsolvable:
            state_name = "unsolvable";
            break;
        case unbounded:
            state_name = "unbounded";
            break;
        default:
            state_name = "bounded";
            break;
        }
        std::cout << "Incorrect state type. Expected unsolvable. Got " << state_name << std::endl;
        return 0;
    }

    printResult(result);

    return 1;
}

int main()
{

    std::vector<std::function<int(void)>> tests = {
        TEST_GENERAL_CASE,
        TEST_MINIMIZE_CASE,
        TEST_WITH_SLACK_CASE,
        TEST_UNBOUNDED_CASE,
        TEST_UNSOLVABLE_CASE};

    int counter = 0;

    for (auto &test : tests)
    {
        counter += test();
    }

    std::cout << "----------------------------RESULTS----------------------------" << std::endl;
    std::cout << "Total number of tests: " << tests.size() << std::endl;
    std::cout << "Total number of passed tests: " << counter << std::endl;

    return 0;
}
