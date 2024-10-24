from pynput import keyboard

def on_press(key):
    try:
        # Get the scan code of the key pressed
        scan_code = key.vk if hasattr(key, 'vk') else None
        print(f'Key pressed: {key} (Scan code: {scan_code})')
    except Exception as e:
        print(f'Error: {e}')

def on_release(key):
    print(f'Key released: {key}')
    # Stop listener on ESC key release
    if key == keyboard.Key.esc:
        return False

# Start listening to the keyboard events
with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
