// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// paloma rodriguez cs405 november 10th 2023 module four

#include <iostream>
#include <stdexcept>  // Include for standard exceptions

// Custom class creation
class CustomException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Custom exception";
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception
    throw std::runtime_error("Standard exception occurred");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Caught std::exception: " << ex.what() << std::endl;
    }

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0)
    {
        throw std::invalid_argument("Division by zero");
    }

    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try
    {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception caught " << ex.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    try
    {

        // TODO: Create exception handlers that catch (in this order):
        //  your custom exception
        //  std::exception
        //  uncaught exception 
        //  that wraps the whole main function, and displays a message to the console.
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& ex)
    {
        // Catch/handle custom exception
        std::cerr << "Caught new exception: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        // Catch/handle std::exception
        std::cerr << "Caught std::exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        // Catch unhandled exceptions
        std::cerr << "Caught an unhandled exception." << std::endl;
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu