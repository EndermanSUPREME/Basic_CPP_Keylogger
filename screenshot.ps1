Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

$outfile = $args

$Screen = [System.Windows.Forms.SystemInformation]::VirtualScreen

# Change to screen size of choice
$Width  = 1920
$Height = 1080

$Left   = $Screen.Left
$Top    = $Screen.Top

$bitmap  = New-Object System.Drawing.Bitmap $Width, $Height
$graphic = [System.Drawing.Graphics]::FromImage($bitmap)
$graphic.CopyFromScreen($Left, $Top, 0, 0, $bitmap.Size)

$bitmap.Save($outfile)
Write-Host "Saved to $outfile"