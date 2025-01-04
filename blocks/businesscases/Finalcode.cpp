#include <iostream>
#include <vector>
#include <string>
#include <sstream> // For trimming spaces
#include <map> // For storing job distribution by location
using namespace std;

// 1. Job Vacancy Database Management
struct Job {
    string industry;
    double salary;
    string requiredSkill;
    string location;
};

// Function to partition the array
int partition(vector<Job>& jobs, int low, int high) {
    double pivot = jobs[high].salary;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (jobs[j].salary <= pivot) {
            i++;
            swap(jobs[i], jobs[j]);
        }
    }
    swap(jobs[i + 1], jobs[high]);
    return i + 1;
}

// Quick Sort implementation
void quickSort(vector<Job>& jobs, int low, int high) {
    if (low < high) {
        int pi = partition(jobs, low, high);
        quickSort(jobs, low, pi - 1);
        quickSort(jobs, pi + 1, high);
    }
}

// Function to display the jobs
void displayJobs(const vector<Job>& jobs) {
    for (const auto& job : jobs) {
        cout << "Industry: " << job.industry
             << ", Salary: " << job.salary
             << ", Required Skill: " << job.requiredSkill
             << ", Location: " << job.location << endl;
    }
}

// 2. Unemployment Rating System
double calculateUnemploymentRate(int unemployed, int totalLaborForce) {
    if (totalLaborForce == 0) {
        cerr << "Error: Total labor force cannot be zero!" << endl;
        return -1.0;
    }
    return (static_cast<double>(unemployed) / totalLaborForce) * 100;
}

// 3. Job Matching System (Using KMP Algorithm)
void computeLPSArray(const string &pattern, vector<int> &lps) {
    int m = pattern.size();
    lps[0] = 0; // LPS[0] is always 0
    int len = 0, i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

bool KMPSearch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> lps(m, 0);
    computeLPSArray(pattern, lps);

    int i = 0, j = 0; // i for text, j for pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            return true; // Pattern found
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return false; // Pattern not found
}

// Function to trim leading/trailing spaces from a string
string trim(const string& str) {
    stringstream ss(str);
    string result, word;
    while (ss >> word) {
        result += word + " ";
    }
    if (!result.empty()) {
        result.pop_back(); // Remove trailing space
    }
    return result;
}

// 4. Job Distribution (Distribute jobs to various locations)
void jobDistributionExample(vector<Job>& jobs) {
    map<string, vector<Job>> jobDistribution; // Map to store jobs by location

    // Distribute jobs based on location
    for (const auto& job : jobs) {
        jobDistribution[job.location].push_back(job);
    }

    // Display job distribution by location
    for (const auto& entry : jobDistribution) {
        cout << "Jobs in " << entry.first << ":\n";
        for (const auto& job : entry.second) {
            cout << "  - Industry: " << job.industry
                 << ", Salary: " << job.salary
                 << ", Required Skill: " << job.requiredSkill << endl;
        }
        cout << endl;
    }
}

// 5. Job Search System (Brute force matching based on skills and location)
vector<int> bruteForceSearch(const string& text, const string& pattern) {
    vector<int> matchPositions;
    int textLength = text.size();
    int patternLength = pattern.size();

    for (int i = 0; i <= textLength - patternLength; ++i) {
        int j = 0;
        while (j < patternLength && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == patternLength) {
            matchPositions.push_back(i); // Pattern found at position i
        }
    }
    return matchPositions;
}
// 6. Economic Inequality Reporting (Matching based on address and skills)
void economicInequalityReporting(vector<Job>& jobs, const vector<string>& jobSeekersSkills) {
    map<string, int> jobCountByLocation;  // To track number of jobs by location
    map<string, int> jobSeekersCountByLocation;  // To track number of job seekers by location

    // Count jobs by location
    for (const auto& job : jobs) {
        jobCountByLocation[job.location]++;
    }

    // Count job seekers by location
    for (const auto& skill : jobSeekersSkills) {
        // Assume job seekers live in the most common location
        // For simplicity, we'll randomly assign location for demonstration
        string location = (skill.find("C++") != string::npos) ? "Hubli" : "Bangalore";
        jobSeekersCountByLocation[location]++;
    }

    // Report on economic inequality based on job distribution and job seeker distribution
    cout << "\nEconomic Inequality Reporting:\n";
    for (const auto& location : jobCountByLocation) {
        cout << "Location: " << location.first << endl;
        cout << "  - Jobs available: " << location.second << endl;
        cout << "  - Job seekers: " << jobSeekersCountByLocation[location.first] << endl;

        if (jobSeekersCountByLocation[location.first] > location.second) {
            cout << "  - Inequality detected: More job seekers than jobs in this location.\n";
        } else if (jobSeekersCountByLocation[location.first] < location.second) {
            cout << "  - Positive distribution: More jobs than job seekers.\n";
        } else {
            cout << "  - Equal distribution: Jobs and job seekers are balanced.\n";
        }
    }
}

int main() {
    int choice;

    do {
        cout << "Select the system you want to use:" << endl;
        cout << "1. Job Vacancy Database Management" << endl;
        cout << "2. Unemployment Rating System" << endl;
        cout << "3. Job Matching System" << endl;
        cout << "4. Job Distribution" << endl;
        cout << "5. Job Search System" << endl;
        cout << "6. Economic Inequality Reporting" << endl;
        cout << "7. Exit" << endl;  // Exit option
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after the choice input

        switch (choice) {
            // ... other cases here ...
            case 1: {
                // 1. Job Vacancy Database Management
                vector<Job> jobs = {
                    {"IT", 70000, "C++", "Hubli"},
                    {"Healthcare", 50000, "Nursing", "Bangalore"},
                    {"Education", 40000, "Teaching", "Hubli"},
                    {"Finance", 60000, "Accounting", "Mumbai"},
                    {"Retail", 30000, "Sales", "Chennai"}
                };

                cout << "Before Sorting (Job Vacancy Database Management):" << endl;
                displayJobs(jobs);

                quickSort(jobs, 0, jobs.size() - 1);

                cout << "\nAfter Sorting by Salary (Job Vacancy Database Management):" << endl;
                displayJobs(jobs);
                break;
            }

            case 2: {
                // 2. Unemployment Rating System
                int unemployed = 15000;       // Example number of unemployed people in Hubli
                int totalLaborForce = 150000; // Example total labor force in Hubli

                double unemploymentRate = calculateUnemploymentRate(unemployed, totalLaborForce);

                if (unemploymentRate != -1.0) {
                    cout << "\nThe current unemployment rate in Hubli is: "
                         << unemploymentRate << "%" << endl;
                }
                break;
            }

            case 3: {
                // 3. Job Matching System
                // Hardcoded job seekers' skills and job requirements
                vector<string> jobSeekersSkills = {"Java C++", "Python JavaScript"};
                vector<string> jobRequirements = {"Java", "Python"};

                cout << "\nMatching Results (Job Matching System):\n";
                for (int i = 0; i < jobSeekersSkills.size(); i++) {
                    cout << "Job Seeker " << i + 1 << " (" << jobSeekersSkills[i] << ") matches:\n";
                    for (int j = 0; j < jobRequirements.size(); j++) {
                        if (KMPSearch(jobSeekersSkills[i], jobRequirements[j])) {
                            cout << "  - Job " << j + 1 << " (" << jobRequirements[j] << ")\n";
                        }
                    }
                }
                break;
            }

            case 4: {
                // 4. Job Distribution
                vector<Job> jobs = {
                    {"IT", 70000, "C++", "Hubli"},
                    {"Healthcare", 50000, "Nursing", "Bangalore"},
                    {"Education", 40000, "Teaching", "Hubli"},
                    {"Finance", 60000, "Accounting", "Mumbai"},
                    {"Retail", 30000, "Sales", "Chennai"}
                };
                // Call Job Distribution function
                jobDistributionExample(jobs);
                break;
            }
case 5: {
                // 5. Job Search System
                // Predefined job database
                vector<string> jobDatabase = {
                    "Software Developer, Hubli, Java and Python, IT",
                    "Data Scientist, Bangalore, Machine Learning and AI, Data Science",
                    "Product Manager, Mumbai, Leadership and Communication, Management",
                    "System Analyst, Hubli, Networking and Systems Design, IT"
                };

                // Preferences of the two employees
                string addressPreference = "Hubli";         // First employee preference
                string skillsPreference = "Machine Learning"; // Second employee preference

                // Match for address preference
                cout << "\nMatching jobs for Address Preference (" << addressPreference << "):\n";
                bool found = false;
                for (const auto& job : jobDatabase) {
                    if (!bruteForceSearch(job, addressPreference).empty()) {
                        cout << "- Job Found: " << job << endl;
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No jobs found for the address preference.\n";
                }

                cout << "\n";

                // Match for skills preference
                cout << "Matching jobs for Skills Preference (" << skillsPreference << "):\n";
                found = false;
                for (const auto& job : jobDatabase) {
                    if (!bruteForceSearch(job, skillsPreference).empty()) {
                        cout << "- Job Found: " << job << endl;
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No jobs found for the skills preference.\n";
                }
                break;
            }


            case 6: {
                // 6. Economic Inequality Reporting
                vector<Job> jobs = {
                    {"IT", 70000, "C++", "Hubli"},
                    {"Healthcare", 50000, "Nursing", "Bangalore"},
                    {"Education", 40000, "Teaching", "Hubli"},
                    {"Finance", 60000, "Accounting", "Mumbai"},
                    {"Retail", 30000, "Sales", "Chennai"}
                };

                vector<string> jobSeekersSkills = {"Java C++", "Python JavaScript", "C++", "Nursing"};

                economicInequalityReporting(jobs, jobSeekersSkills);
                break;
            }

            case 7: {
                cout << "Exiting the program..." << endl;
                break;
            }

            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }

    } while (choice != 7);

    return 0;
}
