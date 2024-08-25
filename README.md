# CommandAnywhere
Execute customized commands by typing specific keywords without any UI, triggering actions like opening the file explorer with a simple Enter.

## Features

- **No UI Interface**: Operate entirely without any graphical interface.
- **Custom Commands**: Set up and execute personalized commands.
- **Simple Trigger**: Execute actions by typing keywords and pressing Enter.

## Usage

1. After running the application, you can use `Win + 'z'` to enter **command typing mode**.
2. Type **predefined keywords** directly using your keyboard (e.g., 'gmp' for **G**oogle **M**a**p**s).
3. Press `Enter` after typing to trigger the corresponding custom command.

## Installation

1. Clone this repository to your local machine:
    ```bash
    git clone https://github.com/ohmyyes1115/CommandAnywhere.git
    ```
2. Build the source code with Visual Studio:
    1. Open `CommandAnywhere.sln` with Visual Studio
    2. Switch the build config to `Release`
    3. Build the solution

## Note
1. In Windows 11, `Win + 'z'` is a built-in hotkey for changing the layout. Need to manually disable this hotkey in advance.

## TODO
- [ ] Allow users to change triggerring hotkey.
- [ ] Allow users to dynamically create basic commands (e.g., launch Explorer with another path).
- [ ] Set up custom keywords and their corresponding basic commands in the configuration file. Example:

```json
{
    "keyword": "proj",
    "exe": "explorer.exe",
    "path": "D:\\project",
}
```
