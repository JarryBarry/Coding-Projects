
import yt_dlp

video_url = input("Enter YouTube Video Link: \n")

# Options for yt-dlp
ydl_opts = {
    'format': 'bestvideo+bestaudio/best',  # Highest quality
    'outtmpl': 'downloads/%(title)s.%(ext)s',  # Save in 'downloads' folder
    'merge_output_format': 'mp4',  # Merge video and audio into MP4
}

try:
    with yt_dlp.YoutubeDL(ydl_opts) as ydl:
        print("Downloading...")
        ydl.download([video_url])
        print("Download completed successfully!")
except Exception as e:
    print(f"Error: {e}")
