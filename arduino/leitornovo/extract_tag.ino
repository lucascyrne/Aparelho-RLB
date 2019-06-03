void extract_tag() {
  uint8_t msg_head = buffer[0];
  uint8_t *msg_data = buffer + 1; // 10 byte => data contains 2byte version + 8byte tag
  uint8_t *msg_data_version = msg_data;
  uint8_t *msg_data_tag = msg_data + 2;
  uint8_t *msg_checksum = buffer + 11; // 2 byte
  uint8_t msg_tail = buffer[13];
  // print message that was sent from RDM630/RDM6300
  Serial.println(" (version)");
  for (int i = 0; i < DATA_TAG_SIZE; ++i) {
    Serial.print(char(msg_data_tag[i]));
  }
  Serial.println(" (tag)");
  Serial.print("Message-Checksum (HEX): ");
  for (int i = 0; i < CHECKSUM_SIZE; ++i) {
    Serial.print(char(msg_checksum[i]));
  }
  Serial.println("");
  Serial.print("Message-Tail: ");
  Serial.println(msg_tail);
  Serial.println("--");
  long tag = hexstr_to_value(msg_data_tag, DATA_TAG_SIZE);
  Serial.print("Extracted Tag: ");
  Serial.println(tag);
  long checksum = 0;
  for (int i = 0; i < DATA_SIZE; i += CHECKSUM_SIZE) {
    long val = hexstr_to_value(msg_data + i, CHECKSUM_SIZE);
    checksum ^= val;
  }
  Serial.print("Extracted Checksum (HEX): ");
  Serial.print(checksum, HEX);
  if (checksum == hexstr_to_value(msg_checksum, CHECKSUM_SIZE)) { // compare calculated checksum to retrieved checksum
    Serial.print(" (OK)"); // calculated checksum corresponds to transmitted checksum!
  } else {
    Serial.print(" (NOT OK)"); // checksums do not match
  }
  Serial.println("");
  Serial.println("--------");
  return tag;
}
long hexstr_to_value(char *str, unsigned int length) { // converts a hexadecimal value (encoded as ASCII string) to a numeric value
  char* copy = malloc((sizeof(char) * length) + 1); 
  memcpy(copy, str, sizeof(char) * length);
  copy[length] = '\0';
  // the variable "copy" is a copy of the parameter "str". "copy" has an additional '\0' element to make sure that "str" is null-terminated.
  long value = strtol(copy, NULL, 16);  // strtol converts a null-terminated string to a long value
  free(copy); // clean up
  return value;
}
