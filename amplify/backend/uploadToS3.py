import boto3
from botocore.exceptions import NoCredentialsError

ACCESS_KEY = 'AKIA2J3NPNJ2IDRBUBUT'
SECRET_KEY = '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'


def upload_to_aws(local_file, bucket, s3_file):
    s3 = boto3.client('s3', aws_access_key_id=ACCESS_KEY,
                      aws_secret_access_key=SECRET_KEY)

    try:
        s3.upload_file(local_file, bucket, s3_file)
        print("Upload Successful")
        return True
    except FileNotFoundError:
        print("The file was not found")
        return False
    except NoCredentialsError:
        print("Credentials not available")
        return False


uploaded = upload_to_aws('flagwords.txt', 'nikhil-test-bucket22', 'hello.txt')