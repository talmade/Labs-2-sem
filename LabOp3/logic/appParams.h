#ifndef APPPARAMS_H
#define APPPARAMS_H

struct TableParams {
    int year;
    double npg;
    double birthRate;
    double deathRate;
    double gdw;
    double urbanization;
    char* republic;
};

struct ParamsUser {
    int column;
    char* republic;
};

struct AppParams {
    TableParams tableParams;
    ParamsUser paramsUser;
};

#endif // APPPARAMS_H
