from __future__ import absolute_import 
from concurrent.futures import process
import imaplib, getpass
import email
from email.header import decode_header
import webbrowser
import os


# account credentials/folder select
username = "hackathontest22@gmail.com"
folder_name = "Inbox"


def clean(text):
    # clean text for creating a folder
    return "".join(c if c.isalnum() else "_" for c in text)
# create an IMAP4 class with SSL 
imap = imaplib.IMAP4_SSL("imap.gmail.com")
# authenticate
password = getpass.getpass("Enter your Password: ")
imap.login(username, password)

status, messages = imap.select("INBOX")
# number of top emails to fetch
N = 3
# total number of emails
messages = int(messages[0])

for i in range(messages, messages-N, -1):
    # fetch the email message by ID
    res, msg = imap.fetch(str(i), "(RFC822)")
    for response in msg:
        if isinstance(response, tuple):
            # parse a bytes email into a message object
            msg = email.message_from_bytes(response[1])
            # decode the email subject
            subject, encoding = decode_header(msg["Subject"])[0]
            if isinstance(subject, bytes):
                # if it's a bytes, decode to str
                subject = subject.decode(encoding)
            # decode email sender
            From, encoding = decode_header(msg.get("From"))[0]
            if isinstance(From, bytes):
                From = From.decode(encoding)
            print("Subject:", subject)
            print("From:", From)
            # if the email message is multipart
            if msg.is_multipart():
                # iterate over email parts
                for part in msg.walk():
                    # extract content type of email
                    content_type = part.get_content_type()
                    content_disposition = str(part.get("Content-Disposition"))
                    try:
                        # get the email body
                        body = part.get_payload(decode=True).decode()
                    except:
                        pass
                    if content_type == "text/plain" and "attachment" not in content_disposition:
                        # print text/plain emails and skip attachments
                        filename = (clean(subject) + ".txt")
                        filepath = os.path.join(folder_name, filename)
                        open(filepath, "w").write(From)
                        open(filepath, "a").write('\n')
                        open(filepath, "a").write('Subject: ')
                        open(filepath, "a").write(subject)
                        open(filepath, "a").write('\n')
                        open(filepath, 'a').write(body)
                    elif "attachment" in content_disposition:
                        # download attachment
                        filename = part.get_filename()
                        if filename:
                            filepath = os.path.join("Attachments", filename)
                            # download attachment and save it
                            open(filepath, "wb").write(part.get_payload(decode=True))
            else:
                # extract content type of email
                content_type = msg.get_content_type()
                # get the email body
                body = msg.get_payload(decode=True).decode()
                if content_type == "text/plain":
                    # print only text email parts
                    filename = (clean(subject) + ".txt")
                    filepath = os.path.join(folder_name, filename)
                    open(filepath, "w").write(From)
                    open(filepath, "a").write('\n')
                    open(filepath, "a").write('Subject: ')
                    open(filepath, "a").write(subject)
                    open(filepath, "a").write('\n')
                    open(filepath, "a").write(body)
            print("="*100)
# close the connection and logout
imap.close()
imap.logout()