#include "std_lib_facilities.h" 

double cm_to_m(double cm)
{
    return cm / 100;
}

double in_to_m(double in)
{
    return in * 0.0254;
}

double ft_to_m(double ft)
{
    return ft * 0.03048;
}

int main() 
{
    vector<string> legal = {"cm", "in", "m", "ft"};

    double entries;
    string unit;
    double max = 0.0;
    double min = 0.0;
    double sum = 0.0;
    int number_of_entries = 0;
    vector<double> every_entry;

    cout << "Enter one number and one unit (cm, m, in or ft): \n";

    while (cin >> entries >> unit) {
        if (std::count(legal.begin(), legal.end(), unit)) {
            sum += entries;
            ++number_of_entries;

            if (unit == "cm") 
                entries = cm_to_m(entries);
            else if (unit == "in")
                entries = in_to_m(entries);
            else if (unit == "ft")
                entries = ft_to_m(entries);

            every_entry.push_back(entries);

            if (max == 0.0 || min == 0.0) {
                max = entries;
                min = entries;
            }
            else if (entries < min) {
                min =  entries;
                cout << "The smallerst so far: " << entries <<"m\n";
            }
            else if (entries > max) {
                max = entries;
                cout << "The largest so far: " << max << "m\n";
            }
        }
        else cout << "Illegal representation of unit\n";
    }

    cout << "The number of entries is: " << number_of_entries << ".\nThe max value is: " << max <<".\nThe min value is: ";
    cout << min << ".\nThe sum of entries is: " << sum << ".\n";
    sort(every_entry);
    cout << "The list of every entry: [";
    for (double x : every_entry) 
        cout << " " << x;
    cout << " ]\n";

    return 0;
}