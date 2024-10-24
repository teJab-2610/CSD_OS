import os
import subprocess
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

class FileChangeHandler(FileSystemEventHandler):
    def on_modified(self, event):
        if event.src_path.endswith('memory.txt'):
            print(f"{event.src_path} has been modified.")
            self.run_commands()

    def run_commands(self):
        try:
            # Run the first command
            subprocess.run(['./vis.exe'], check=True)
            # Run the second command
            subprocess.run(['python', 'mem_conv.py'], check=True)
            print("Commands executed successfully.")
        except subprocess.CalledProcessError as e:
            print(f"Error occurred: {e}")

if __name__ == "__main__":
    path = '.'
    event_handler = FileChangeHandler()
    observer = Observer()
    observer.schedule(event_handler, path, recursive=False)
    
    print(f"Monitoring changes in {path}/memory.txt...")
    observer.start()

    try:
        while True:
            time.sleep(1)  # Keep the script running
    except KeyboardInterrupt:
        observer.stop()
    observer.join()
