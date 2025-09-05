import requests
import time

# ThingSpeak channel details
channel_id = _YOUR_CHANNEL_ID_
read_url = f'https://api.thingspeak.com/channels/{channel_id}/feeds.json'
params = {
    'results': 1  # Get the latest entry
}

while True:
    try:
        response = requests.get(read_url, params=params)
        if response.status_code == 200:
            data = response.json()
            latest_entry = data['feeds'][0]
            temperature = latest_entry['field1']
            humidity = latest_entry['field2']
            timestamp = latest_entry['created_at']

            print(f"Timestamp: {timestamp}")
            print(f"Temperature: {temperature}°C")
            print(f"Humidity: {humidity}%")
        else:
            print(f"Failed to fetch data. HTTP {response.status_code}")
    except Exception as e:
        print(f"Error fetching data: {e}")

    time.sleep(10)  # Wait before next fetch
