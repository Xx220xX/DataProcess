//
// Created by PC on 01/08/2019.
//

#ifndef CPP_DATAPROCESS_H
#define CPP_DATAPROCESS_H
/**
 * @param source
 *      raw data source for extraction, matches in the following format: "command:[[string]]% [number]"
 *      example: "set Wifi: name = [[wifi name]] password [[wifi password]] port = 8080"
 *      command = "setWifi"
 *      data1 = "wifi name"
 *      data2 = "wifi password"
 *      data3 = 8080
 * @param command
 *      corresponds to a command to be executed. If it is the same as the command contained in the source,
 *      the data is extracted according to formatting and the return is true.
 * @param format
 *      format in which data will be extracted
 *      There are 4 cases.
 *      d - for integers
 *      f - float
 *      g - for double
 *      s [size] - for string, where size is an integer for the maximum string length.
 * @param ...
 *      These must match pointers to variables, which are in the same order as the format specifies.
 *
 * @return if found the command in the source returns true, false if not found.
 *
 * @example
 *         loadCommand("setWifi: name = [[wifi_name]] pass = [[my_password]]","setWifi","s[100] s[100]",pstr_name,pstr_pass);
 *               The command will be found and the data removed. at the end of the function we will have:
 *               pstr_nome = "wifi_name"
 *               pstr_pass = "my_password"
 *
 *         other:
 *         int day,month,year;
 *         float temperature;
 *         double humidity;
 *         char str[201];
 *         char source[] = "setTime:01/08/2019 46.03 F humidity 86.9 [[this is amazing]] ";
 *         loadCommand(source,"setTime","d d d f g s[200]",&day,&month,&year,&temperature,&humidity,str);
 *
 *
 */
bool loadCommand(const char *source, const char *command, const char *format, ...);

/***
 * @param source :data source containing the number to be captured
 * @param bg :initial index to take into account, at the end of the function it is in the position where the last buff character was taken
 * @return the first double found
 */
double nextDouble(const char *source, int *bg= 0);
/***
 * @param source: data source containing the number to be captured
 * @param bg : initial index to take into account, at the end of the function it is in the position where the last buff character was taken
 * @return the first int  found
 * @example
 *      int index =0
 *      double a = nextDouble("find your number here 1.82 or here 22.6",&index);//returned 1.82
 *      double b = nextDouble("find your number here 1.82 or here 22.6",&index);//returned 22.6
*/
int nextInt(const char *source, int *bg =0);

#endif //CPP_DATAPROCESS_H
