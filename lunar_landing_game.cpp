#include <iostream>
#include <cmath>
#include <string>
#include <cstdio>
using namespace std;

int main() {
  string again = "YES";
  cout << "CONTROL CALLING LUNAR MODULE. MANUAL CONTROL IS NECESSARY\n";
  cout << "YOU MAY RESET FUEL RATE K EACH 10 SECS TO 0 OR ANY VALUE\n";
  cout << "BETWEEN 8 & 200 LBS/SEC. YOU'VE 16000 LBS FUEL. ESTIMATED\n";
  cout << "FREE FALL IMPACT TIME-120 SECS. CAPSULE WEIGHT-32500 LBS\n";

  while (again == "YES") {
    double A = 120, V = 1, M = 32500, N = 16500, G = 0.001, Z = 1.8, L = 0, S = 0, T = 0, K = 0, J = 0, I = 0, miles, feet;
    

    cout << "FIRST RADAR CHECK COMING UP\n\n\n";
    cout << "COMMENCE LANDING PROCEDURE\n";
    cout << "TIME,SECS   ALTITUDE,MILES+FEET   VELOCITY,MPH   FUEL,LBS   FUEL RATE\n";

    L = 0;
  
    start_turn:
    feet = modf(A, &miles);
    printf("%8.0f%15.0f%7.0f%15.2f%12.1f      ", L, miles, 5280 * feet, 3600 * V, M - N);
      
    prompt_for_k:
    cout << "K=:";
    while (!(cin >> K) || K < 0 || ((0 < K) && (K < 8)) || K > 200) {
      cout << "NOT POSSIBLE...................................................";
      cout << "K=:";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    T = 10;

    turn_loop:
    while (true) {
      if (M - N < 0.001) goto fuel_out;
      if (T < 0.001) goto start_turn;
      S = T;

      if (N + S * K - M > 0) S = (M - N) / K;

      double Q = S * K / M;
      double Q_2 = pow(Q, 2);
      double Q_3 = pow(Q, 3);
      double Q_4 = pow(Q, 4);
      double Q_5 = pow(Q, 5);

      J = V + G * S + Z * (-Q - Q_2 / 2 - Q_3 / 3 - Q_4 / 4 - Q_5 / 5);
      I = A - G * S * S / 2 - V * S + Z * S * (Q / 2 + Q_2 / 6 + Q_3 / 12 + Q_4 / 20 + Q_5 / 30);

      if (I <= 0) goto loop_until_on_the_moon;

      L += S;
      T -= S;
      M -= S * K;
      A = I;
      V = J;
    }

    loop_until_on_the_moon:
    while (S >= 0.005) {
      S = 2 * A / (V + sqrt(V * V + 2 * A * (G - Z * K / M)));

      double Q = S * K / M;
      double Q_2 = pow(Q, 2);
      double Q_3 = pow(Q, 3);
      double Q_4 = pow(Q, 4);
      double Q_5 = pow(Q, 5);

      J = V + G * S + Z * (-Q - Q_2 / 2 - Q_3 / 3 - Q_4 / 4 - Q_5 / 5);
      I = A - G * S * S / 2 - V * S + Z * S * (Q / 2 + Q_2 / 6 + Q_3 / 12 + Q_4 / 20 + Q_5 / 30);

      if (I <= 0) goto loop_until_on_the_moon;

      L += S;
      T -= S;
      M -= S * K;
      A = I;
      V = J;
    }
    goto on_the_moon;

    fuel_out:
    cout << "FUEL OUT AT ";
    printf("%.2f SECS\n", L);

    S = (sqrt(V * V + 2 * A * G) - V) / G;
    V += G * S;
    L += S;

    on_the_moon:
    cout << "ON THE MOON AT   ";
    printf("%.2f SECS\n", L);

    double W = 3600 * V;
    cout << "IMPACT VELOCITY OF  ";
    printf("%.2f  M.P.H.\n", W);

    cout << "FUEL LEFT: ";
    printf("%.2f  LBS\n", M-N);

    if (W <= 1)
      cout << "PERFECT LANDING !-(LUCKY)\n";
    else if (W <= 10)
      cout << "GOOD LANDING-(COULD BE BETTER)\n";
    else if (W <= 22)
      cout << "CONGRATULATIONS ON A POOR LANDING\n";
    else if (W <= 40)
      cout << "CRAFT DAMAGE. GOOD LUCK\n";
    else if (W <= 60)
      cout << "CRASH LANDING-YOU'VE 5 HRS OXYGEN\n";
    else
      cout << "SORRY,BUT THERE WERE NO SURVIVORS-YOU BLEW IT!\n"
      << "IN FACT YOU BLASTED A NEW LUNAR CRATER  ";
    printf("%.2f FT. DEEP\n", W * 0.277777);

    cout << "\n\n\n\nTRY AGAIN?\n(ANS. YES OR NO):";
    cin >> again;

    while (again!= "YES" && again != "NO") {
      cout << "(ANS. YES OR NO):";
      cin >> again;
    }
  }
  cout << "CONTROL OUT\n\n\n";
  return 0;
}