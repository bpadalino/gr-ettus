/* -*- c++ -*- */
/*
 * Copyright 2019 Ettus Research, a National Instruments Brand.
 * Copyright 2020 Ettus Research, A National Instruments Brand.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * gr-ettus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gr-ettus; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_ETTUS_RFNOC_TX_RADIO_H
#define INCLUDED_ETTUS_RFNOC_TX_RADIO_H

#include <ettus/api.h>
#include <ettus/rfnoc_block.h>
#include <ettus/rfnoc_graph.h>

namespace gr {
namespace ettus {

/*! RFNoC TX Radio
 *
 * This wraps a radio block into GNU Radio. Note: When doing TX and RX in the
 * same flow graph, simply crate an rfnoc_rx_radio and an rfnoc_tx_radio with
 * the same block ID.
 *
 * \ingroup uhd_blk
 */
class ETTUS_API rfnoc_tx_radio : virtual public rfnoc_block
{
public:
    typedef boost::shared_ptr<rfnoc_tx_radio> sptr;

    /*!
     * \param graph Reference to the underlying rfnoc_graph object
     * \param block_args Additional block arguments
     * \param device_select Device Selection
     * \param instance Instance Selection
     */
    static sptr make(rfnoc_graph::sptr graph,
                     const ::uhd::device_addr_t& block_args,
                     const int device_select,
                     const int instance);

    //! Set the input sampling rate of the radio block
    //
    // Note: The actual rate of the radio will be coerced to whatever it is
    // capable of.
    //
    // \param rate The new sampling rate
    virtual double set_rate(const double rate) = 0;

    //! Set the antenna for this radio
    //
    // \param antenna The antenna name (e.g., "RX2"). Valid name depend on the
    //                underlying hardware.
    // \param chan The channel for which this antenna setting is for
    virtual void set_antenna(const std::string& antenna, const size_t chan) = 0;

    //! Set the TX frequency for this radio
    //
    // \param frequency The received frequency (e.g., 1e9)
    // \param chan The channel for which this frequency setting is for
    virtual double set_frequency(const double frequency, const size_t chan) = 0;

    //! Configure the tune args for this RX radio
    //
    // \param args The new args (e.g., "mode_n=1")
    // \param chan The channel for which this setting is for
    virtual void set_tune_args(const ::uhd::device_addr_t& args, const size_t chan) = 0;

    //! Configure the overall gain for this TX radio
    //
    // \param gain The new gain value (in dB)
    // \param chan The channel for which this setting is for
    virtual double set_gain(const double gain, const size_t chan) = 0;

    //! Configure a specific gain for this RX radio
    //
    // \param gain The new gain value (in dB)
    // \param name The gain stage name to set
    // \param chan The channel for which this setting is for
    virtual double
    set_gain(const double gain, const std::string& name, const size_t chan) = 0;

    //! Switch the gain profile for this RX radio
    //
    // \param profile The name of the gain profile (e.g., "default")
    // \param chan The channel for which this setting is for
    virtual void set_gain_profile(const std::string& profile, const size_t chan) = 0;

    //! Set the analog bandwidth for this RX radio
    //
    // \param bandwidth The new bandwidth, in Hz
    // \param chan The channel for which this setting is for
    virtual double set_bandwidth(const double bandwidth, const size_t chan) = 0;

    //! Set the LO source for this TX radio
    //
    // Note: Available sources depend on the underlying hardware.
    //
    // \param source The new LO source (e.g., "internal")
    // \param name The LO name (e.g. "LO1")
    // \param chan The channel for which this setting is for
    virtual void set_lo_source(const std::string& source,
                               const std::string& name,
                               const size_t chan) = 0;

    //! Enable/disable LO export for this TX radio
    //
    // \param enabled When true, export this LO
    // \param name The LO name (e.g. "LO1")
    // \param chan The channel for which this setting is for
    virtual void set_lo_export_enabled(const bool enabled,
                                       const std::string& name,
                                       const size_t chan) = 0;

    //! Configure the LO frequency explicitly
    //
    // Consult uhd::rfnoc::radio_control::set_tx_lo_freq() for more details.
    // \param freq The new LO frequency
    // \param name The LO name (e.g. "LO1")
    // \param chan The channel for which this setting is for
    virtual double
    set_lo_freq(const double freq, const std::string& name, const size_t chan) = 0;

    //! Set the DC offset value explicitly
    //
    // Consult uhd::rfnoc::radio_control::set_tx_dc_offset() for more details.
    //
    // \param offset The DC offset value that gets used for compensation
    // \param chan The channel for which this setting is for
    virtual void set_dc_offset(const std::complex<double>& offset, const size_t chan) = 0;

    //! Set the I/Q imbalance correction value explicitly
    //
    // Consult uhd::rfnoc::radio_control::set_tx_iq_balance() for more details.
    //
    // \param offset The DC offset value that gets used for compensation
    // \param chan The channel for which this setting is for
    virtual void set_iq_balance(const std::complex<double>& correction,
                                const size_t chan) = 0;
};

} // namespace ettus
} // namespace gr

#endif /* INCLUDED_ETTUS_RFNOC_TX_RADIO_H */
