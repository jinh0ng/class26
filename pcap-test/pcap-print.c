#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <libnet.h>
#include "pcap-test.h"

void print_mac_addr(uint8_t *mac){

	//print ex) 00:12:34:56:78:90
	for(int i=0; i<6; i++){
		printf("%02x", mac[i]);
		if(i!=5)printf(":");
	}

	return;
}


void print_ip_addr(struct in_addr ip){
	
	char	*str = inet_ntoa(ip);
	printf("%s\n", str);
	
	return;
}

/*void print_port(uint16_t port){

	//ntohs(port)필요할듯 ->%5d로 프린트
	
	return;
}
*/
void print_eth(struct libnet_ethernet_hdr *ethernet_header){
	
	printf("MAC	src: ");
	print_mac_addr(ethernet_header->ether_shost);
	printf("\nMAC	src: ");
	print_mac_addr(ethernet_header->ether_dhost);

	return;
}


void print_ip(struct libnet_ipv4_hdr *ipv4_header){
	printf("\nIP	src: ");
	print_ip_addr(ipv4_header->ip_src);
	printf("IP	dstL ");
	print_ip_addr(ipv4_header->ip_dst);
	
	return;
}


void print_tcp(struct libnet_tcp_hdr *tcp_hdr){
	//print_port(tcp_hdr->th_sport);
	//print_port(tcp_hdr->th_dport);
	
	return;
}


/*void print_data(const uint8_t *packet, uint8_t data_base, uint8_t data_len){
	//len == 0 일 때: 0이라고 표시출력
	if(data_len == 0){
		printf("No Data\n");
	}
	//len >  8 일때 예외처리 (len=8이라고 임의로 만들어주고 출력)
	if(data_len > 8)data_len = 8;
	
	for(int i=0; i < data_len; i++){
		printf("%02x ", packet[data_base+i]);
	}
	
	return;
}
*/
