$start = 3
$end = 10

Write-Host "Running Tests"
for ($i = $start; $i -le $end; $i++) {
    Write-Host "`nTesting with input: $i"
    .\cmake-build-debug/GrayCodeVector.exe $i
}