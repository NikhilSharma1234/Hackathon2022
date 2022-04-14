import imaplib, getpass, re
pattern_uid = re.compile(r'\d+ \(UID (?P<uid>\d+)\)')

def connect(email):
    imap = imaplib.IMAP4_SSL("imap.gmail.com")
    password = getpass.getpass("Enter your Password: ")
    imap.login(email, password)
    return imap

def disconnect(imap):
    imap.logout()

def parse_uid(data):
    match = pattern_uid.match(data)
    return match.group('uid')

if __name__ == '__main__':
    imap = connect('hackathontest22@gmail.com')
    imap.select(mailbox = 'INBOX', readonly = False)
    resp, items = imap.search(None, 'All')
    email_ids  = items[0].split()
    latest_email_id = email_ids[-1] # Assuming that you are moving the latest email.

    resp, data = imap.fetch(latest_email_id, "(UID)")
    msg_uid = parse_uid(data[0].decode("utf-8", "ignore"))
       
    result = imap.uid('COPY', msg_uid, 'Spam')

    if result[0] == 'OK':
        mov, data = imap.uid('STORE', msg_uid , '+FLAGS', '(\Deleted)')
        imap.expunge()

    disconnect(imap)