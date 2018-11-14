#!/bin/sh

set -ex

publish="$1"

osmo-clean-workspace.sh

$MAKE $PARALLEL_MAKE
$MAKE $PARALLEL_MAKE check

if [ "x$publish" = "x--publish" ]; then
  mkdir out/
  cp */*.pdf out/

  cat > "$WORKSPACE/known_hosts" <<EOF
[rita.osmocom.org]:48 ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDDgQ9HntlpWNmh953a2Gc8NysKE4orOatVT1wQkyzhARnfYUerRuwyNr1GqMyBKdSI9amYVBXJIOUFcpV81niA7zQRUs66bpIMkE9/rHxBd81SkorEPOIS84W4vm3SZtuNqa+fADcqe88Hcb0ZdTzjKILuwi19gzrQyME2knHY71EOETe9Yow5RD2hTIpB5ecNxI0LUKDq+Ii8HfBvndPBIr0BWYDugckQ3Bocf+yn/tn2/GZieFEyFpBGF/MnLbAAfUKIdeyFRX7ufaiWWz5yKAfEhtziqdAGZaXNaLG6gkpy3EixOAy6ZXuTAk3b3Y0FUmDjhOHllbPmTOcKMry9
[rita.osmocom.org]:48 ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBPdWn1kEousXuKsZ+qJEZTt/NSeASxCrUfNDW3LWtH+d8Ust7ZuKp/vuyG+5pe5pwpPOgFu7TjN+0lVjYJVXH54=
[rita.osmocom.org]:48 ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIK8iivY70EiR5NiGChV39gRLjNpC8lvu1ZdHtdMw2zuX
EOF
  SSH_COMMAND="ssh -o 'UserKnownHostsFile=$WORKSPACE/known_hosts' -p 48"
  rsync -avz --delete -e "$SSH_COMMAND" ./out/ docs@rita.osmocom.org:web-files/latest/
fi

osmo-clean-workspace.sh
