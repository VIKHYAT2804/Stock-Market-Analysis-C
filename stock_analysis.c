#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STOCKS 100
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    double price[5];
    double pe;
    double debtRatio;
    double revenueGrowth;
    double profitMargin;
    double roe;
    double revenuePast[5];
    double profitPast[5];
} Stock;

// --- Utility Functions ---
double calculate_mean(double arr[], int n) {
    double sum = 0;
    for(int i=0;i<n;i++) sum += arr[i];
    return sum/n;
}

double calculate_std(double arr[], int n) {
    double mean = calculate_mean(arr, n);
    double sum_sq = 0;
    for(int i=0;i<n;i++) sum_sq += (arr[i]-mean)*(arr[i]-mean);
    return sqrt(sum_sq/(n-1));
}

// --- CSV Loader ---
int load_csv(const char* filename, Stock stocks[], int* count) {
    FILE* fp = fopen(filename,"r");
    if(!fp) return 0;

    char line[1024];
    int idx=0;
    fgets(line,sizeof(line),fp); // skip header

    while(fgets(line,sizeof(line),fp)) {
        Stock s;
        char *token = strtok(line,",");
        strcpy(s.name, token);

        // Prices
        for(int i=0;i<5;i++){
            token = strtok(NULL,",");
            s.price[i] = atof(token);
        }

        // Metrics
        token = strtok(NULL,","); s.pe = atof(token);
        token = strtok(NULL,","); s.debtRatio = atof(token);
        token = strtok(NULL,","); s.revenueGrowth = atof(token);
        token = strtok(NULL,","); s.profitMargin = atof(token);
        token = strtok(NULL,","); s.roe = atof(token);

        // Revenue past 5 years
        for(int i=0;i<5;i++){
            token = strtok(NULL,",");
            s.revenuePast[i] = atof(token);
        }

        // Profit past 5 years
        for(int i=0;i<5;i++){
            token = strtok(NULL,",");
            s.profitPast[i] = atof(token);
        }

        stocks[idx++] = s;
    }
    *count = idx;
    fclose(fp);
    return 1;
}

// --- Find stock by name ---
int find_stock(Stock stocks[], int count, char* name) {
    for(int i=0;i<count;i++)
        if(strcmp(stocks[i].name,name)==0) return i;
    return -1;
}

// --- Options ---
void investment_advice(Stock s){
    double revenueGrowth5yr = (s.revenuePast[4] - s.revenuePast[0]) / (s.revenuePast[0]>0?s.revenuePast[0]:1);
    double avgProfitMargin = 0.0;
    for(int i=0;i<5;i++)
        avgProfitMargin += s.profitPast[i]/(s.revenuePast[i]>0?s.revenuePast[i]:1);
    avgProfitMargin /= 5.0;

    printf("\n--- Investment Advice for %s ---\n", s.name);
    printf("5-Year Revenue Growth: %.2f%%\n", revenueGrowth5yr*100);
    printf("Average Profit Margin: %.2f%%\n", avgProfitMargin*100);
    printf("P/E Ratio: %.2f\n", s.pe);
    printf("Debt Ratio: %.2f\n", s.debtRatio);

    if (revenueGrowth5yr >=0.3 && avgProfitMargin>=0.1 && s.pe>=10 && s.pe<=25 && s.debtRatio<0.5)
        printf("Recommendation: GOOD for LONG-TERM HOLD\n");
    else
        printf("Recommendation: MODERATE or RISKY\n");
}

void volatility_analysis(Stock s){
    double returns[4];
    for(int i=1;i<5;i++)
        returns[i-1] = (s.price[i]-s.price[i-1])/s.price[i-1];

    double avg = calculate_mean(returns,4);
    double vol = calculate_std(returns,4);

    printf("\n--- Volatility Analysis for %s ---\n", s.name);
    printf("Average Daily Return: %.2f%%\n", avg*100);
    printf("Volatility (Std Dev): %.2f%%\n", vol*100);
}

void short_term_trend(Stock s){
    double change = s.price[4]-s.price[3];
    printf("\n--- Short-term Trend Prediction for %s ---\n", s.name);
    if(change>0.01) printf("Trend: UP\n");
    else if(change<-0.01) printf("Trend: DOWN\n");
    else printf("Trend: STABLE\n");
}

void compare_stocks(Stock s1, Stock s2){
    printf("\n--- Comparing %s vs %s ---\n", s1.name, s2.name);
    printf("%-15s %-10s %-10s %-10s\n","Stock","P/E","DebtR","RevGr");
    printf("%-15s %-10.2f %-10.2f %-10.2f\n",s1.name,s1.pe,s1.debtRatio,s1.revenueGrowth);
    printf("%-15s %-10.2f %-10.2f %-10.2f\n",s2.name,s2.pe,s2.debtRatio,s2.revenueGrowth);

    // Simple scoring
    int score1=0, score2=0;
    if(s1.pe>=10 && s1.pe<=25) score1++; else score2++;
    if(s2.pe>=10 && s2.pe<=25) score2++; else score1++;
    if(s1.debtRatio<0.5) score1++; else score2++;
    if(s2.debtRatio<0.5) score2++;
    if(s1.revenueGrowth>=0.3) score1++; else score2++;
    if(s2.revenueGrowth>=0.3) score2++;

    printf("Better stock: %s\n", (score1>=score2)?s1.name:s2.name);
}

// --- Main ---
int main(){
    Stock stocks[MAX_STOCKS];
    int count;

    if (!load_csv("C:\\Users\\VIKHYAT AGRAWAL\\OneDrive\\Desktop\\python by umme haani\\nifty50_full_5yr.csv", stocks, &count)) {
    printf("Error: Could not open CSV file.\n");
    return 1;
}

    int choice;
    char name1[50], name2[50];

    do{
        printf("\n===== STOCK ANALYSIS MENU =====\n");
        printf("1. Investment Advice\n");
        printf("2. Volatility Analysis\n");
        printf("3. Short-term Trend Prediction\n");
        printf("4. Compare Two Stocks\n");
        printf("5. Exit\n");
        printf("Enter choice: "); scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Enter stock name: "); scanf("%s",name1);
                int idx1 = find_stock(stocks,count,name1);
                if(idx1!=-1) investment_advice(stocks[idx1]);
                else printf("Stock not found.\n");
                break;
            case 2:
                printf("Enter stock name: "); scanf("%s",name1);
                idx1 = find_stock(stocks,count,name1);
                if(idx1!=-1) volatility_analysis(stocks[idx1]);
                else printf("Stock not found.\n");
                break;
            case 3:
                printf("Enter stock name: "); scanf("%s",name1);
                idx1 = find_stock(stocks,count,name1);
                if(idx1!=-1) short_term_trend(stocks[idx1]);
                else printf("Stock not found.\n");
                break;
            case 4:
                printf("Enter first stock name: "); scanf("%s",name1);
                printf("Enter second stock name: "); scanf("%s",name2);
                idx1 = find_stock(stocks,count,name1);
                int idx2 = find_stock(stocks,count,name2);
                if(idx1!=-1 && idx2!=-1) compare_stocks(stocks[idx1],stocks[idx2]);
                else printf("One or both stocks not found.\n");
                break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }

    }while(choice!=5);

    return 0;
}
