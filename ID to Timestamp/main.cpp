#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>

#define print(x, ...) printf_s(x, __VA_ARGS__)

#define DISCORD_EPOCH 1420070400000

std::string unixTimeToHumanReadable(__int64 seconds)
{

    using namespace std;

    // Save the time in Human
    // readable format
    string ans = "";

    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    long int currYear, daysTillNow, extraTime,
        extraDays, index, date, month, hours,
        minutes, secondss, flag = 0;

    // Calculate total days unix time T
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;

    // Calculating current year
    while (daysTillNow >= 365) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0
                && currYear % 100 != 0)) {
            daysTillNow -= 366;
        }
        else {
            daysTillNow -= 365;
        }
        currYear += 1;
    }

    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;

    if (currYear % 400 == 0
        || (currYear % 4 == 0
            && currYear % 100 != 0))
        flag = 1;

    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {

            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays
                    - daysOfMonth[index]
                    < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {

            if (extraDays
                - daysOfMonth[index]
                < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }

    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }

    // Calculating HH:MM:YYYY
    hours = (extraTime / 3600) - 3;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;


    // Convert UTC to UTC-3
    if (hours == -3)
    {
        hours = 21;
        date--;
    }  
    if (hours == -2)
    {
        hours = 22;
        date--;
    }
    if (hours == -1)
    {
        hours = 23;
        date--;
    }

    if (date <= 9)
    {
        ans += "0";
        ans += to_string(date);
    }
    else
        ans += to_string(date);

    ans += "/";

    if (month <= 9)
    {
        ans += "0";
        ans += to_string(month);
    }
    else
        ans += to_string(month);

    ans += "/";

    if (currYear <= 9)
    {
        ans += "0";
        ans += to_string(currYear);
    }
    else
        ans += to_string(currYear);

    ans += " ";

    if (hours <= 9)
    {
        ans += "0";
        ans += to_string(hours);
    }
    else
        ans += to_string(hours);

    ans += ":";

    if (minutes <= 9)
    {
        ans += "0";
        ans += to_string(minutes);
    }
    else
        ans += to_string(minutes);

    ans += ":";

    if (secondss <= 9)
    {
        ans += "0";
        ans += to_string(secondss);
    }
    else
        ans += to_string(secondss);

    // Return the time
    return ans;
}

int main()
{
    SetConsoleTitleA("ID to Timestamp");

    // Wait for ID
    __int64 id = 0;
    print("Cole o ID aqui >> ");
    scanf_s("%lld", &id);

    // Calcule id to UNIX Timestamp: https://discord.com/developers/docs/reference#convert-snowflake-to-datetime
    id = ((id >> 22) + DISCORD_EPOCH) / 1000;

    // Print date and time
    std::cout << unixTimeToHumanReadable(id) << "\n";

    system("pause");

    return 0;
}