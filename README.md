# 🏧 ATM Simulation Program (C Language)

## 📌 Overview

This project is a **console-based ATM Simulation Program** written in C by a B.Tech CSE student.
It mimics basic ATM operations such as balance checking, deposit, withdrawal, PIN management, and transaction history.

---

## 🚀 Features

* 🔐 Secure 4-digit PIN login (hidden input)
* 💰 Balance checking
* 📥 Deposit money
* 💸 Withdrawal (Domestic & International)
* 📱 OTP-based withdrawal (mobile verification)
* 🔁 Money transfer
* 🧾 Transaction history (last 20 transactions)
* 🔄 Change PIN (with file storage)
* 💾 File handling (PIN saved permanently)

---

## 🛠️ Technologies Used

* C Programming Language
* Standard Libraries:

  * `stdio.h`
  * `conio.h`
  * `string.h`
  * `stdlib.h`
  * `time.h`

---

## 📂 File Structure

```
ATM-Simulation/
│
├── atm.c          # Main source code
├── pin.txt        # Stores user PIN (auto-created)
└── README.md      # Project documentation
```

---

## ▶️ How to Run

### 🔧 Using Turbo C / CodeBlocks / GCC

1. Copy the code into a file named:

   ```
   atm.c
   ```

2. Compile the program:

   ```
   gcc atm.c -o atm
   ```

3. Run the program:

   ```
   ./atm
   ```

---

## 🔑 Default Login Details

* **Default PIN:** `1234`
* You can change the PIN using the "Change PIN" option.
* New PIN is saved in `pin.txt`.

---

## ⚠️ Important Notes

* `conio.h` is used for hidden PIN input (`getch()`), which may not work on all compilers.
* For Linux/Mac, replace `getch()` with alternative methods.
* OTP is simulated (displayed on screen).

---

## 📸 Sample Menu

```
===== ATM MENU =====

1. Check Balance  
2. Deposit Money  
3. Withdraw Money  
4. Withdraw with Mobile OTP  
5. Transaction History  
6. Transfer Money  
7. Change PIN  
8. Exit  
```

---

## 📈 Future Improvements

* Add user authentication with multiple accounts
* Encrypt PIN storage
* GUI version using C++ or Python
* Database integration

---

## 👨‍💻 Author

**B.Tech CSE Student**
ATM Simulation Project

---

## 📜 License

This project is for **educational purposes only**.

---

## ⭐ Support

If you like this project:

* ⭐ Star the repository
* 🍴 Fork it
* 🛠️ Improve it

---
