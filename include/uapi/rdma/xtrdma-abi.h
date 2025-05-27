#ifndef XTRDMA_ABI_H
#define XTRDMA_ABI_H

#include <linux/types.h>

#define XTRDMA_ABI_VER 5
#define XTRDMA_IPV6_ADDR_LENGTH 16 

struct xtrdma_ib_alloc_context_req {
	__u8 userspace_ver;
	__u8 rsvd[7];
};

struct xtrdma_ib_alloc_context_resp {
	__u64 map_offset;
	__u64 feature_flags;
	__u32 max_hw_wq_sge;
	__u32 max_hw_read_sge;
	__u32 max_hw_inline_data;
	__u32 max_hw_wq_wr;
	__u32 min_hw_qp_size;
	__u32 max_hw_qp_size;
	__u32 min_hw_cq_size;
	__u32 max_hw_cq_size;
	__u32 min_hw_srq_size;
	__u32 max_hw_srq_size;
	__u32 max_hw_srq_wr;
	__u32 hmc_page_size;
	__u32 srfq_ctx_page_size;
	__u32 qpc_size;
	__u32 cqc_size;
	__u32 srfqc_size;
	__u8 srqe_size;
	__u8 sq_rq_wqe_size;
	__u8 min_cqe_size;
	__u8 max_cqe_size;
	__u8 hw_ver;
	__u8 rsvd[3];
};

struct xtrdma_alloc_pd_resp {
	__u32 pd_id;
	__u8 rsvd[4];
};

struct xtrdma_create_ah_resp {
	__u32 src_addr_idx; 
	__u32 ah_id;
	__u32 pd_idx;
	__u16 vlan_id;
	__u16 dst_vport_id; /* Reserved */
	__u8 fwd; /* Reserved */
	__u8 pri;
	__u8 dst_port;
	bool lag; /* Reserved */
	bool cfi;	
	bool vlan_flag;
	bool ipv4;
	bool do_mult;
	__u8 dmac[ETH_ALEN];
	__u8 dest_ip_addr[XTRDMA_IPV6_ADDR_LENGTH];
	__u8 recv[2];	
};

struct xtrdma_ib_create_srq_req {
	__aligned_u64 srq_buf_addr;
	__aligned_u64 srfq_buf_addr;
	__u8 srq_huge_mem_enable;
	__u8 srfq_huge_mem_enable;
	__u8 rsvd[6];
};

struct xtrdma_ib_create_srq_resp {
	__u64 map_offset;
	__u32 srqn;
	__u16 shadow_area_addr_offset;
	__u8 srq_sn;
	__u8 rsvd;
};

struct xtrdma_create_cq_req {
	__aligned_u64 user_cq_buf;
	__u32 user_cq_buf_size;
	__u8 big_mem_enable;
	__u8 huge_mem_enable;
	__u8 cqe_size_idx;
	__u8 inline_cqe_enable;
};

struct xtrdma_create_cq_resp {
	__u64 map_offset;
	__u32 cq_id;
	__u16 shadow_area_addr_offset;
	__u16 rsvd;
};

struct xtrdma_resize_cq_req {
	__aligned_u64 user_cq_buf;
	__u32 user_cq_buf_size;
	__u8 huge_mem_enable;
	__u8 cqe_size_idx;
	__u8 rsv[2];
};

struct xtrdma_ib_create_qp_req {
	__aligned_u64 sq_buf_addr;
	__aligned_u64 rq_buf_addr;
	__u8 sq_huge_mem_enable;
	__u8 rq_huge_mem_enable;
	__u8 rsvd[6];
};

struct xtrdma_ib_create_qp_resp {
	__u64 map_offset;
	__u64 shadow_addr_offset;
	__u32 qpn;
	__u8 qp_sn;
	__u8 dst_port;
	__u8 rsvd[2];
};

#endif
