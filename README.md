# Daily Habit Tracker

**Team Members**  
- Wonmin Shin (<ws2301@nyu.edu>)  
- Seo Kwak (<sk9575@nyu.edu>)  

---

## Description

The **Daily Habit Tracker** is a command-line interface (CLI) application written in C++ to help you build and sustain productive routines by logging and reviewing your daily habits. It supports:

- User registration and login  
- Habit creation, editing, deletion, and categorization  
- Daily check-ins to mark habits as completed or skipped  
- Progress tracking with simple ASCII charts in the terminal  
- Local data storage (JSON or SQLite) for easy backup and portability  

---

## Table of Contents

- [Features](#features)  
- [Building](#building)  
- [Usage](#usage)  
- [Contributing](#contributing)  
- [License](#license)  
- [Contact](#contact)  

---

## Features

### User Features

- **Register / Login**  
  Create a new account or log in to access your personal habit dashboard.

- **Create Habits**  
  Define a new habit by specifying a name, frequency (daily, weekly, etc.), and category (e.g., Health, Study, Fitness).

- **Edit Habits**  
  Update existing habits—change the name, frequency, or category at any time.

- **Delete Habits**  
  Remove habits that are no longer relevant to your goals.

- **Group & Categorize**  
  Organize habits under custom categories to focus on different aspects of your life.

- **Daily Check-Ins**  
  Mark each habit as “completed” or “skipped” each day through a simple prompt.

- **View Progress**  
  See your habit completion rates over time, rendered as a basic ASCII chart in the terminal.

- **Notifications & Reminders**  
  Configure optional system notifications or terminal alerts to remind you to check in.

---

## Building

1. **Clone the repository**  
   ```bash
   git clone https://github.com/your-username/daily-habit-tracker.git
   cd daily-habit-tracker
