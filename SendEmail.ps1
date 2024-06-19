powershell -c "C:/Users/Public/Documents/lockdown/screenshot.ps1 $args"

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12;

# Set variables consisting on the email being sent
$From = "sender@mail.server"; $To = "recv@mail.server";
$Subject = "Testing Silent Alarm"; $Body = "Lockdown has flagged '$badword'! Take action ASAP!";
$Attachments = $args
$Password = "App Passwd" | ConvertTo-SecureString -AsPlainText -Force;
$Credential = New-Object System.Management.Automation.PSCredential -ArgumentList $From, $Password;

# Send the email (Secure GMAIL but can be changed to send from any smtp server of choice) and perform clean up
Send-MailMessage -From $From -To $To -Subject $Subject -Body $Body -Attachments $Attachments -SmtpServer "smtp.gmail.com" -port 587 -UseSsl -Credential $Credential
powershell -c "rm $args"