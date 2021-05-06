#include <iostream>

int print_strings(void)
{
    std::cout << std::endl << "Please run executable with solely any of the following numbers" << std::endl << std::endl;

    std::cout << "   1 = daily rider frequency distribution" << std::endl;
    std::cout << "   2 = monthly frequency distribution for preferred day" << std::endl;
    std::cout << "   3 = growth rate by segment week-to-week" << std::endl;
    std::cout << "   4 = total, maximum, average and minimum ride distance by rider frequency" << std::endl;
    std::cout << "   5 = How many days, on average, do our customers stay in the ‘Active’ segment" << std::endl << std::endl;

    std::cout << "Executable will run certain query on the \"b_total_rides_info\" table " << std::endl << std::endl;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1][1] != 0)
        return print_strings();
    if (argv[1][0] == '1'){
        std::cout << std::endl << "   Daily rider frequency distribution" << std::endl << std::endl;
        system("psql -U wester -d postgres -c \"`cat c_frequency_distribution`\"");
    }
    else if (argv[1][0] == '2'){
        std::cout << std::endl << "   Monthly frequency distribution for preferred day" << std::endl << std::endl;
        system("psql -U wester -d postgres -c \"`cat c_monthly_distribution_preferred_day`\"");
    }
    else if (argv[1][0] == '3'){
        std::cout << std::endl << "   Growth rate by segment week-to-week" << std::endl << std::endl;
        system("psql -U wester -d postgres -c \"`cat c_growth_rate_by_segment`\"");
    }
    else if (argv[1][0] == '4'){
        std::cout << std::endl << "   Total, maximum, average and minimum ride distance by rider frequency" << std::endl << std::endl;
        system("psql -U wester -d postgres -c \"`cat c_distance_by_rider_frequency`\"");
    }
    else if (argv[1][0] == '5'){
        std::cout << std::endl << "   How many days, on average, do our customers stay in the ‘Active’ segment" << std::endl << std::endl;
        system("psql -U wester -d postgres -c \"`cat c_consecutive_days_active_average`\"");
    }
    else 
        return print_strings();
    return 0;
}
