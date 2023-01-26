## Next Combination Mask
int next_combs_mask(int mask) {
  int lsb = -mask & mask;
  return (((mask + lsb) ^ mask) / (lsb << 2)) | (mask + lsb);
}
## Iterate over submask in decreasing order
for (int submask=mask; submask > 0; submask = (submask-1)&mask) {
  // do stuff
}